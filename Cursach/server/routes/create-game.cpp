#include "create-game.h"

namespace RouteCreateGame {

   size_t getMinSid(json games) {
      if (games.size() == 0) return 0;

      size_t prevSid = 0;

      for (auto& game : games) {
         size_t sid = game["sid"].get<size_t>();
         if (sid - prevSid > 1) return prevSid + 1;
         prevSid = sid;
      }
      
      return prevSid + 1;
   }
   
   void GetHandler(const Request& req, Response& res) {

   }

   void PostHandler(const Request& req, Response& res) {
      std::cout << "Create Game: Post\n";

      std::string creatorId = req.get_param_value("id");

      auto gamesFile = new File(File::pwd() + "/../data/game.json");

      json games = gamesFile->readJson();
      json gameTpl = File::ReadJson(File::pwd() + "/../data/default-game.json");
      
      int sid = getMinSid(games);
      
      // Updating default values
      gameTpl["sid"] = sid;
      games.push_back(gameTpl);

      gamesFile->writeJson(games, 3);
      
      res.set_content("{ \"status\": \"OK\", \"sid\": " + std::to_string(sid) + "}", "text/json; charset=UTF-8");
      std::cout << "Create Game: responded with SID " << sid << std::endl;
   }
   
} // RouteCreateGame
