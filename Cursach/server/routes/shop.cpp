#include "shop.h"
namespace RouteShop {

   json readUsers() {
      return File::ReadJson(File::pwd() + "/../data/users.json");
   }

   void saveUsers(json users) {
      File::WriteJson(File::pwd() + "/../data/users.json", users, 3);
   }
   
   void GetHandler(const Request& req, Response& res) {

   }

   void PostHandler(const Request& req, Response& res) {
      std::cout << "Shop: Post" << std::endl;

      std::string action = req.get_param_value("action");
      size_t id = std::stoi( req.get_param_value("id") );

      std::cout << "Shop: Incoming action = " << action << " (id:" << id << ")" << std::endl;
      
      json::iterator targetUser;
      json users = readUsers();
      
      std::cout << "Shop: Users read successfully" << std::endl;

      // Find user with target id
      for (auto it = users.begin(); it != users.end(); it++) {
         json user = *it;
         auto userIt = it;
         if (user["id"].get<size_t>() == id) {
            targetUser = userIt;
            break;
         }
      }

      if (targetUser->is_null())
         std::cout << "Shop: No user selected (id: " << id << ")" << std::endl;
      else
         std::cout << "Shop: User found successfully" << std::endl;
         

      // Switch (action)

      if (action == "get-state") { // case "get-state":
         // Mode: Get state
         std::cout << "Shop: Mode = get-state" << std::endl;
         
         res.set_content(json{
            {"status", "OK"},
            {"shop", (*targetUser)["shop"].dump()},
            {"amount", (*targetUser)["amount"]},
         }.dump(), "text/json; charset=UTF-8");
      } // break;
      else if (action == "select") { // case "select":
         // Mode: select
         std::cout << "Shop: Mode = select" << std::endl;

         std::string sliderName = req.get_param_value("slider");
         std::string productName = req.get_param_value("product");

         // FUCK THIS C++!!!
         json& targetShop = (*targetUser)["shop"][sliderName];
         for (auto it = targetShop.begin(); it != targetShop.end(); it++) {
            std::string key = it.key(), 
               val = it.value();
            
            std::cout << key << ": " << val << std::endl;
            
            if (val == "selected") {
               targetShop[key] = "select";
               std::cout << "Shop: User(" << id << ")[shop][" << sliderName << "][" << key << "] is UNselected" << std::endl;
            }
         }

         targetShop[productName] = "selected";
         std::cout << "Shop: User(" << id << ")[shop][" << sliderName << "][" << productName << "] is selected";

         saveUsers(users);
         
         res.set_content(R"({ "status": "OK" })", "text/json; charset=UTF-8");
      } // break;
      else if (action == "buy") { // case "buy":
         // Mode: buy
         std::cout << "Shop: Mode = buy" << std::endl;

         std::string sliderName = req.get_param_value("slider");
         std::string productName = req.get_param_value("product");

         size_t productPrice = File::ReadJson(File::pwd() + "/../data/price.json")[sliderName][productName].get<size_t>();
         size_t userAmount = (*targetUser)["amount"].get<size_t>();
         
         if (productPrice > userAmount) {
            std::cout << "Shop: Deal deprecated (" << userAmount << " < " << productPrice << ")";
            res.set_content(R"({ "status": "Deprecated" })", "text/json; charset=UTF-8");
            return;
         }
         // else if enough money
         
         userAmount -= productPrice;
         (*targetUser)["amount"] = userAmount;

         json& targetShop = (*targetUser)["shop"][sliderName];
         targetShop[productName] = "select";
         std::cout << "Shop: User(" << id << ")[shop][" << sliderName << "][" << productName << "] was bought";

         saveUsers(users);
         
         res.set_content(R"({ "status": "OK" })", "text/json; charset=UTF-8");
      } // break;
      else { // default:
         // Mode: Unexpected
         std::cout << "Shop: Error \"Unexpected action\"" << std::endl;
         res.set_content(R"({ "status": "Error", "message": "Unexpected action" })", "text/json; charset=UTF-8");
      } // break;
   }
   
} // RouteShop
