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
   
   size_t getReadyCount(size_t sid) {
      json game = getGameData(sid);
      size_t count = 0;

      for (auto user : game["users"]) {
         if (user["ready"].get<bool>())
            count++;
      }

      return count;
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
      
      // Action: Get-skin
      else if (action == "get-skin") {
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
         sendAll(sid, id, "ready-count-update", json{
            {"count", getReadyCount(sid)},
         });
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