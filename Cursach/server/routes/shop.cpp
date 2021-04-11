#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;

namespace RouteShop {
   
   void GetHandler(const Request& req, Response& res) {

   }

   void PostHandler(const Request& req, Response& res) {
      std::cout << "Shop: Post" << std::endl;

      std::string action = req.get_param_value("action");
      size_t id = std::stoi( req.get_param_value("id") );

      std::cout << "Shop: Action = " << action << " (" << id << ")" << std::endl;
      

      // Switch (action)

      if (action == "get-state") { // case "get-state":
         // Mode: Get state
         std::cout << "Shop: Mode = get-state" << std::endl;
         
         json targetUser;
         json users = File::ReadJson(File::pwd() + "/../data/users.json");

         for (auto it = users.begin(); it != users.end(); it++) {
            json user = *it;
            if (user["id"].get<size_t>() == id) {
               targetUser = user;
               break;
            }
         }
         
         res.set_content(json{
            {"status", "OK"},
            {"shop", targetUser["shop"].dump()},
            {"amount", targetUser["amount"]},
         }.dump(), "text/json; charset=UTF-8");
      } // break;
      else { // default:
         // Mode: Unexpected
         std::cout << "Shop: Error \"Unexpected action\"" << std::endl;
      } // break;
   }
   
} // RouteShop
