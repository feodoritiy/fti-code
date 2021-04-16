#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;
#include <File/File.h>
#include <limits>

namespace RouteCreateGame {
   void GetHandler(const Request& req, Response& res);
   void PostHandler(const Request& req, Response& res);
} // RouteCreateGame

