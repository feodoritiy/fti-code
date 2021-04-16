#include <iostream>
#include <string>
#include <File/File.h>
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>

using namespace httplib;
using json = nlohmann::json;

Server server;

const char* SERVER_HOST = "127.0.0.1";
const int SERVER_PORT = 1234;

#include "routes/root.h"
#include "routes/register.h"
#include "routes/login.h"
#include "routes/create-game.h"
#include "routes/game.h"
#include "routes/shop.h"

int main() {
   server.set_keep_alive_timeout(30); // timeout 30 sec

   server
      .Get("/", RouteRoot::Handler)
      .Post("/", RouteRoot::Handler)
      
      .Get("/register", RouteRegister::GetHandler)
      .Post("/register", RouteRegister::PostHandler)

      .Get("/login", RouteLogin::GetHandler)
      .Post("/login", RouteLogin::PostHandler)

      .Post("/create-game", RouteCreateGame::PostHandler)

      .Get("/game", RouteGame::GetHandler)
      .Post("/game", RouteGame::PostHandler)

      .Get("/shop", RouteShop::GetHandler)
      .Post("/shop", RouteShop::PostHandler);


   // Starting server
   std::cout << "Server started on " << SERVER_HOST << ":" << SERVER_PORT << "\n";
   server.listen(SERVER_HOST, SERVER_PORT);

   return 0;
}