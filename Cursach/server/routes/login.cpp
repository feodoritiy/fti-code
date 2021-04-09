#include <iostream>
#include <string>

#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;

#include <File/File.h>


namespace RouteLogin {
   
   void GetHandler(const Request& req, Response& res) {

   }

   void PostHandler(const Request& req, Response& res) {
      std::cout << "Login: Post" << std::endl;

      std::string login = req.get_param_value("login");
      std::string password = req.get_param_value("password");

      File usersFile(File::pwd() + "/../data/users.json");
      json users = usersFile.readJson();

      for (auto it = users.begin(); it != users.end(); it++) {
         auto user = it.value();
         if (user["login"] == login) {
            if (user["password"] == password) {
               std::cout << "Login: Found (" << login << ", " << password << ")" << std::endl;
               std::cout << "Login: Response " << R"({ "status": "OK", "id": )" + std::to_string(user["id"].get<size_t>()) + " }" << std::endl;
               res.set_content(
                  R"({ "status": "OK", "id": )" + std::to_string(user["id"].get<size_t>()) + " }", 
                  "text/json; charset=UTF-8"
               );
            } else { // user["password"] != password
               std::cout << "Login: Wrong password (" << login << ", " << password << ")" << std::endl;
               res.set_content(R"({ "status": "Wrong-password" })", "text/json; charset=UTF-8");
            }
            return;
         }
      }

      res.set_content(R"({ "status": "Wrong-login" })", "text/json; charset=UTF-8");
   }
   
} // RouteLogin