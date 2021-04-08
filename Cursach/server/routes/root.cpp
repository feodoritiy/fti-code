#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
using namespace httplib;

namespace RouteRoot {
   void Handler(const Request& req, Response& res) {
      res.set_content("Hello, World!", "text/html; charset=UTF-8");
   }
}