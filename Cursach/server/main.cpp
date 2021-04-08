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

#include "routes/root.cpp"
#include "routes/register.cpp"
#include "routes/create-game.cpp"
#include "routes/connect-to-game.cpp"
#include "routes/exit-game.cpp"
#include "routes/step.cpp"
#include "routes/shop.cpp"

int main() {

   server
      .Get("/", RouteRoot::Handler)
      .Post("/", RouteRoot::Handler)
      
      .Get("/register", RouteRegister::GetHandler)
      .Post("/register", RouteRegister::PostHandler)

      .Get("/create-game", RouteCreateGame::GetHandler)
      .Get("/connect-to-game", RouteConnectToGame::GetHandler)
      .Get("/exit-game", RouteExitGame::GetHandler)

      .Get("/step", RouteStep::GetHandler)
      .Post("/step", RouteStep::PostHandler)

      .Get("/shop", RouteShop::GetHandler)
      .Post("/shop", RouteShop::PostHandler);


   // Starting server
   std::cout << "Server started on " << SERVER_HOST << ":" << SERVER_PORT << "\n";
   server.listen(SERVER_HOST, SERVER_PORT);

   return 0;
}