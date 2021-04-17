#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for erase-remove idiom
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;
#include <File/File.h>

namespace RouteGame {
   json getGameData(size_t sid);
   std::string getUserSkin(size_t id);
   
   std::string pwd = File::pwd();

   std::string getParam(const Request& req, std::string paramName) {
      if (!req.has_param(paramName.c_str())) {
         std::cout << "Error getParam: Trying to get param \"" + paramName + "\", but no such param in req\n";
         throw "Error getParam: Trying to get param \"" + paramName + "\", but no such param in req\n";
      }
      
      return req.get_param_value(paramName.c_str());
   }
   
   void answer_json(Response& res, std::string action, json data) {
      data["action"] = action;
      res.set_content(data.dump().c_str(), "text/json; charset=UTF-8");
   }

   json getGameData(size_t sid) {
      File* gameFile = new File(File::pwd() + "/../data/game.json");
      json games = gameFile->readJson();

      json* targetGame;
      for (json& game : games) {
         if (game["sid"].get<size_t>() == sid) {
            targetGame = &game;
            break;
         }
      }
      
      return *targetGame;
   }
   json getGameOrder(size_t sid) {
      json users = getGameData(sid)["users"];

      json res = json::array();
      for (auto& user : users) {
         json userData;
         
         size_t id = user["id"].get<size_t>();
         userData["id"] = id;
         
         std::string figureName = user["figure"].get<std::string>(),
            figureNameUpper;
         if (figureName == "x") figureNameUpper = "X";
         else if (figureName == "o") figureNameUpper = "O";
         else if (figureName == "p") figureNameUpper = "P";
         else if (figureName == "t") figureNameUpper = "T";
         else if (figureName == "r") figureNameUpper = "R";
         userData["skin"] = getUserSkin(id) + figureNameUpper;

         res.push_back(userData);
      }

      std::random_shuffle(res.begin(), res.end());

      return res;
   }
   
   size_t getReadyCount(size_t sid) {
      json game = getGameData(sid);
      size_t count = 0;

      for (auto user : game["users"]) {
         if (user["ready"].get<bool>())
            count++;
      }

      return count;
   }
   size_t getConnectionCount(size_t sid) {
      json game = getGameData(sid);
      return game["users"].size();
   }

   void withGame(size_t sid, std::function<void(json game)> callback) {
      json game = getGameData(sid);
      callback(game);
   }
   void withUser(size_t id, std::function<void(json user)> callback) {
      File* userFile = new File(pwd + "/../data/users.json");
      json users = userFile->readJson();

      for (auto user : users) {
         if (user["id"].get<size_t>() == id) {
            callback(user);
            return;
         }
      }
   }
   void updateUser(size_t id, std::function<void(json& user)> callback) {
      File* userFile = new File(pwd + "/../data/users.json");
      json users = userFile->readJson();

      for (auto& user : users) {
         if (user["id"].get<size_t>() == id) {
            callback(user);
            break;
         }
      }

      userFile->writeJson(users, 3);
   }
   
   std::string getUserSkin(size_t id) {
      std::string skinName;

      // search for user selected skin
      withUser(id, [&](json user){
         json figuresState = user["shop"]["figure"];
         for (auto it = figuresState.begin(); it != figuresState.end(); it++) {
            auto key = it.key();
            auto val = it.value().get<std::string>();

            if (val == "selected") {
               skinName = key;
               break;
            }
         }
      });
      
      return skinName;
   }
   
   void sendAll(size_t sid, size_t senderId, std::string action, json data) {
      data["action"] = action;
      data["sender_id"] = senderId;
      std::cout << "Game, sendAll: action '" << action << "' with data " << data.dump() << '\n';

      json game = getGameData(sid);
      for (json user : game["users"]) {
         std::string userHost = user["host"].get<std::string>();
         userHost = "http://" + userHost;
         Client* userServer = new Client(userHost.c_str());
         userServer->Post("/", data.dump(), "application/json");
      }
   }
   
   void updateGameData(size_t sid, std::function<void(json* game)> callback) {
      File* gameFile = new File(pwd + "/../data/game.json");
      json games = gameFile->readJson();

      json* targetGame;
      for (json& game : games) {
         if (game["sid"].get<size_t>() == sid) {
            targetGame = &game;
            break;
         }
      }
      
      callback(targetGame);
      gameFile->writeJson(games, 3);
   }

   void updateGameUser(size_t id, size_t sid, std::function<void(json*)> callback) {
      updateGameData(sid, [&](json* game){
         // find target user
         json* targetUser;
         for (json& user : (*game)["users"]) {
            if (user["id"].get<size_t>() == id) {
               targetUser = &user;
            }
         }

         callback(targetUser);
      });
   }
   
   void updateCell(size_t sid, size_t i, size_t j, std::function<size_t(json*)> callback) {
      updateGameData(sid, [&](json* game){
         json& field = game->at("field");
         field[i][j] = callback(&field[i][j]);
      });
   }
   
   struct CheckWinResult {
      bool isWin;
      size_t id;
   };
   class CheckCell {
   public:
      bool isValue;
      size_t value;

      CheckCell(json field, size_t i, size_t j) {
         this->isValue = !field[i][j].is_null();
         if (this->isValue) {
            this->value = field[i][j].get<size_t>();
         }
      }
   };
   bool operator== (CheckCell& lhs, CheckCell& rhs) {
      if (!lhs.isValue)
         return false;
      if (!rhs.isValue)
         return false;
      return lhs.value == rhs.value;
   }
   CheckWinResult checkWin(size_t sid) {
      using CheckLine = std::vector<CheckCell>;
      using CheckLines = std::vector<CheckLine>;
      
      const int winSize = 3;
      
      auto searchSequence = [&](CheckLines lines) {
         CheckLine line;

         for (auto lineIt = lines.begin(); lineIt != lines.end(); lineIt++) {
            int sequence = 0;

            line = *lineIt;
            CheckCell lastId = line[0];
            
            for (auto& currId : line) {
               if (currId == lastId) {
                  sequence++;
               } else {
                  sequence = 1;
                  lastId = currId;
               }

               if (sequence >= winSize) {
                  struct CheckWinResult res = {true, currId.value};
                  return res;
               }
            }
         }

         struct CheckWinResult res = {false, 0};
         return res;
      };

      auto getDiag = [&](json field, int startI, int startJ, int boundI, int boundJ, bool reverse = false){
         CheckLine diag;

         int differI = boundI - startI;
         int differJ = boundJ - startJ;

         if (differI < 0) differI *= -1;
         if (differJ < 0) differJ *= -1;

         int minDiffer = differI < differJ ? differI : differJ;
         
         for (int c = 0; c < minDiffer; c++) {
            int i = startI + c,
               j = startJ + (reverse ? -c : c);
            diag.push_back(*new CheckCell(field, i, j));
         }

         return diag;
      };
      json field = getGameData(sid)["field"];
      
      CheckLines rows;
      for (int i = 0; i < 5; i++) {
         CheckLine row;
         for (int j = 0; j < 8; j++) {
            row.push_back(*new CheckCell(field, i, j));
         }
         rows.push_back(row);
      }
      auto rowsRes = searchSequence(rows);
      if (rowsRes.isWin) return rowsRes;

      CheckLines cols;
      for (int j = 0; j < 8; j++) {
         CheckLine col;
         for (int i = 0; i < 5; i++) {
            col.push_back(*new CheckCell(field, i, j));
         }
         cols.push_back(col);
      }
      auto colsRes = searchSequence(cols);
      if (colsRes.isWin) return colsRes;
      
      CheckLines mainDiags;
      for (int i = 0; i < 5; i++)
         mainDiags.push_back(getDiag(field, i, 0, 5, 8));
      for (int j = 1; j < 8; j++)
         mainDiags.push_back(getDiag(field, 0, j, 5, 8));
      auto mainDiagsRes = searchSequence(mainDiags);
      if (mainDiagsRes.isWin) return mainDiagsRes;

      CheckLines subDiags;
      for (int i = 0; i < 5; i++)
         subDiags.push_back(getDiag(field, i, 7, 5, -1, true));
      for (int j = 0; j < 7; j++)
         subDiags.push_back(getDiag(field, 0, j, 5, -1, true));
      auto subDiagsRes = searchSequence(subDiags);
      if (subDiagsRes.isWin) return subDiagsRes;
            
      struct CheckWinResult res = {false, 0};
      return res;
   }


   struct registerGameUserResult {
      size_t connectionCount;
      json usedFigures;
   };
   registerGameUserResult registerGameUser(size_t sid, size_t id, std::string host) {
      registerGameUserResult res;

      updateGameData(sid, [&](json* game){
         json userTpl = File::ReadJson(File::pwd() + "/../data/default-game-user.json");
         userTpl["id"] = id;
         userTpl["host"] = host;

         (*game)["users"].push_back(userTpl);
         res.connectionCount = (*game)["users"].size();

         json figures = json::array();
         for (auto user : (*game)["users"]) {
            auto figure = user["figure"].get<std::string>();
            if (figure != "")
               figures.push_back(figure);
         }
         res.usedFigures = figures;
      });

      return res;
   }
   
   size_t deleteGameUser(size_t id, size_t sid) {
      size_t connectionCount;

      updateGameData(sid, [&](json* game){
         int i = 0;

         for (auto& user : game->at("users")) {
            if (user["id"].get<size_t>() == id) {
               (*game)["users"].erase(game->at("users").begin() + i);
               break;
            } i++;
         }

         connectionCount = game->at("users").size();
      });

      return connectionCount;
   }
   
   void deleteGame(size_t sid) {
      File* gameFile = new File(pwd + "/../data/game.json");
      json games = gameFile->readJson();

      size_t i = 0;
      for (json& game : games) {
         if (game["sid"].get<size_t>() == sid)
            break;
         i++;
      }
      
      games.erase(games.begin() + i);
      gameFile->writeJson(games, 3);
   }


   void GetHandler(const Request& req, Response& res) {

   }

   
   void PostHandler(const Request& req, Response& res) {
      std::cout << "Game: Post\n";

      size_t id = std::stoi(getParam(req, "id"));
      size_t sid = std::stoi(getParam(req, "sid"));
      std::string action = getParam(req, "action");

      std::cout << "Game: Action '" << action << "' from user (id: " << id << ", sid: " << sid << ")\n";


      // Action: Connect     
      if (action == "connect") {
         std::string host = getParam(req, "host");
         std::cout << "Game: Connect action, with host " << host << "\n";

         auto registerRes = registerGameUser(sid, id, host);
         std::cout << "Game: Connection count become " << registerRes.connectionCount << "\n";

         answer_json(res, action, json{
            {"status", "OK"},
            {"connection_count", registerRes.connectionCount},
         });
         
         sendAll(sid, id, "connection-count-update", json{
            {"count", registerRes.connectionCount},
         });
      }
      
      // Action: Step
      else if (action == "step") {
         std::string skin = getParam(req, "skin"); 
         
         size_t i = std::stoi(getParam(req, "i")), 
            j = std::stoi(getParam(req, "j"));

         updateCell(sid, i, j, [&](json* cell){
            if (cell->is_null()) {
               return id;
            } // warning because return not always
         });
         
         sendAll(sid, id, action, json{
            {"i", i},
            {"j", j},
         });
         answer_json(res, action, json{
            {"status", "OK"},
         });
         auto winInfo = checkWin(sid);
         if (winInfo.isWin) {
            sendAll(sid, id, "win", json{
               {"winner", winInfo.id},
            });
            updateUser(winInfo.id, [&](json& user){
               auto amount = user.at("amount").get<size_t>();
               user.at("amount") = amount + 10000;
            });
         }
         std::cout << "Game: Step respond\n";
      }
      
      // Action: Get-skin
      else if (action == "get-skin") {
         std::string skinName = getUserSkin(id);
         // sending answer
         answer_json(res, action, json{
            {"status", "OK"},
            {"skin", skinName},
         });
      }

      // Action: Get-field-skin
      else if (action == "get-field-skin") {
         std::string skinName;
         // search for user selected skin
         withUser(id, [&](json user){
            json fieldState = user["shop"]["field"];
            for (auto it = fieldState.begin(); it != fieldState.end(); it++) {
               auto key = it.key();
               auto val = it.value().get<std::string>();

               if (val == "selected") {
                  skinName = key;
                  break;
               }
            }
         });
         // sending answer
         answer_json(res, action, json{
            {"status", "OK"},
            {"skin", skinName},
         });
      }
      
      // Action: Get-connections-state
      else if (action == "get-connections-state") {
         json figures = json::array();
         withGame(sid, [&](json game){
            for (auto& user : game["users"]) {
               std::string figure = user["figure"].get<std::string>();
               if (figure != "")
                  figures.push_back(figure);
            }
         });
         answer_json(res, action, json{
            {"status", "OK"},
            {"figures", figures},
            {"ready_count", getReadyCount(sid)},
         });
      }

      // Action: Figure-select
      else if (action == "figure-select") {
         std::string figureType = getParam(req, "figure");
         
         bool figureUsed = false;
         withGame(sid, [&](json game){
            for (auto user : game["users"]) {
               if (user["figure"].get<std::string>() == figureType) {
                  figureUsed = true;
                  break;
               }
            }
         });

         if (!figureUsed) {
            updateGameUser(id, sid, [&](json* user){
               (*user)["figure"] = figureType; // update user figure
            });
            answer_json(res, action, json{
               {"status", "OK"},
            });
            sendAll(sid, id, action, json{
               {"status", "OK"},
               {"figure", figureType},
            });
         }
         else { // figure is used
            answer_json(res, action, json{
               {"status", "Error"},
               {"message", "Figure already used"},
            });
         }
      }

      // Action: Figure-unselect
      else if (action == "figure-unselect") {
         std::string figureType = getParam(req, "figure");
         
         updateGameUser(id, sid, [&](json* user){
            (*user)["figure"] = ""; // update user figure
         });
         answer_json(res, action, json{
            {"status", "OK"},
         });
         sendAll(sid, id, action, json{
            {"status", "OK"},
            {"figure", figureType},
         });
      }
      
      // Action: Ready
      else if (action == "ready") {
         updateGameUser(id, sid, [&](json* user){
            (*user)["ready"] = true;
         });
         answer_json(res, action, json{});
         size_t readyCount = getReadyCount(sid),
            connectionCount = getConnectionCount(sid);
         sendAll(sid, id, "ready-count-update", json{
            {"count", readyCount},
         });
         if (readyCount == connectionCount && (2 <= readyCount && readyCount <= 5)) {
            sendAll(sid, id, "game-start", json{
               {"order", getGameOrder(sid)},
            });
         }
      }

      // Action: Unready
      else if (action == "unready") {
         updateGameUser(id, sid, [&](json* user){
            (*user)["ready"] = false;
         });
         answer_json(res, action, json{});
         sendAll(sid, id, "ready-count-update", json{
            {"count", getReadyCount(sid)},
         });
      }
      
      // Action: disconnect
      else if (action == "disconnect") {
         std::string figureName;
         updateGameUser(id, sid, [&](json* user){
            figureName = user->at("figure").get<std::string>();
         });
         
         size_t connectionCount = deleteGameUser(id, sid);

         answer_json(res, action, json{});
         sendAll(sid, id, "figure-unselect", {
            {"figure", figureName},
         });
         sendAll(sid, id, "connection-count-update", json{
            {"count", connectionCount},
         });
         sendAll(sid, id, "ready-count-update", json{
            {"count", getReadyCount(sid)},
         });
         
         if (connectionCount == 0) {
            deleteGame(sid);
         }
      }
      
      
   }
   
   
} // RouteGame