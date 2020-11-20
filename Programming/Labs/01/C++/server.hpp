#ifndef SERVER
#define SERVER

#include "./include/cpp_httplib/httplib.h"
using namespace httplib;

#include "./tools/Weather.cpp"
#include "./json.hpp"

#endif

#ifndef ASK_URL
#include "./tools/askUrl.cpp"
#endif