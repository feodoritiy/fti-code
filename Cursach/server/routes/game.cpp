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
   
   void sendAll(size_t sid, std::string action, json data) {
      data["action"] = action;
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
      File* gameFile = new File(File::pwd() + "/../data/game.json");
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

   size_t registerGameUser(size_t sid, size_t id, std::string host) {
      size_t connectionCount;

      updateGameData(sid, [&](json* game){
         json userTpl = File::ReadJson(File::pwd() + "/../data/default-game-user.json");
         userTpl["id"] = id;
         userTpl["host"] = host;
         
         (*game)["users"].push_back(userTpl);
         connectionCount = (*game)["users"].size();
      });

      return connectionCount;
   }


   void GetHandler(const Request& req, Response& res) {

   }

   void PostHandler(const Request& req, Response& res) {
      std::cout << "Game: Post\n";

      size_t id = std::stoi(getParam(req, "id"));
      size_t sid = std::stoi(getParam(req, "sid"));
      std::string action = getParam(req, "action");

      std::cout << "Game: Action '" << action << "' from user (id: " << id << ", sid: " << sid << ")\n";

      if (action == "connect") {
         std::string host = getParam(req, "host");
         std::cout << "Game: Connect action, with host " << host << "\n";

         size_t connectionCount = registerGameUser(sid, id, host);
         std::cout << "Game: Connection count become " << connectionCount << "\n";

         answer_json(res, action, json{
            {"status", "OK"},
            {"connection_count", connectionCount},
         });
         
         sendAll(sid, action, json{
            {"connection_count", connectionCount},
         });
      }
   }
   
} // RouteGame