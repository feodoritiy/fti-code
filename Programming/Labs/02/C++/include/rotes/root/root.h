#pragma once

#include <json/json.hpp>
using json = nlohmann::json;
#include <cpp_httplib/httplib.h>
using namespace httplib;

#include <tools/replaceAll.h>
#include <HooksPage/HooksPage.h>

extern HooksPage webhooksPage;

namespace RouteRoot {

   const std::string DIALOGS_JSON_PATH = File::pwd() + "/../json/dialog";

   std::string dialog(std::string dialogName, json state, json config = R"({})"_json);

   void Handler(const Request& req, Response& res);

   std::string getCommand(json yandexJson);

   std::string getProductName(json yandexJson, int productTokenIndex);
   json getProductSet(json yandexJson, int productTokenIndex);
   void removeProduct(int productTokenIndex, json& yandexJson, json& state);

   std::string rubleString(int number);
} // namespace RouteRoot