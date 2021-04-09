#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
#include <File/File.h>
using namespace httplib;
using json = nlohmann::json;

namespace RouteRegister {
   
   void GetHandler(const Request& req, Response& res) {

   }

   void PostHandler(const Request& req, Response& res) {
      std::cout << "Register: Post" << std::endl;

      std::string login = req.get_param_value("login");
      std::string password = req.get_param_value("password");

      json defaultUser = File::ReadJson(File::pwd() + "/../data/default-user.json");

      File usersFile(File::pwd() + "/../data/users.json");
      json users = usersFile.readJson();
      
      size_t maxId = 0, newId;

      defaultUser["login"] = login;
      defaultUser["password"] = password;
      
      for (auto it = users.begin(); it != users.end(); it++) {
         auto user = it.value();
         if (user["login"] == login) {
            std::cout << "Register: Fail (" << login << ", " << password << ")" << std::endl;
            res.set_content(R"({ "status": "Exists" })", "text/json; charset=UTF-8");
            return;
         } else {
            maxId = user["id"].get<size_t>();
         }
      }

      newId = maxId + 1;
      defaultUser["id"] = newId;

      users.push_back(defaultUser);
      usersFile.writeJson(users, 3);

      res.set_content(
         R"({ "status": "OK", "id": )" + std::to_string(newId) + " }", 
         "text/json; charset=UTF-8"
      );
   }
   
} // RoutRegister