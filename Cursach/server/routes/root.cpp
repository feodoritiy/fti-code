#include "root.h"
namespace RouteRoot {
   void Handler(const Request& req, Response& res) {
      res.set_content("Use Python client to communicate with server!!", "text/html; charset=UTF-8");
   }
}