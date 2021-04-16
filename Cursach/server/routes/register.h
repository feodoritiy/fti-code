#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
#include <File/File.h>
using namespace httplib;
using json = nlohmann::json;

namespace RouteRegister {
   void GetHandler(const Request& req, Response& res);
   void PostHandler(const Request& req, Response& res);
} // RoutRegister