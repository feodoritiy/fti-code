#pragma once

#include <HooksPage/HooksPage.h>

#include <json/json.hpp>
using json = nlohmann::json;
#include <cpp_httplib/httplib.h>
using namespace httplib;

extern HooksPage webhooksPage;

void webhooksRoteHandler(const Request& req, Response& res);