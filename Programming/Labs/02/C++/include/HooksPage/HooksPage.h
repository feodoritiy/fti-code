#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <File/File.h>
#include <tools/replaceAll.h>
#include <json/json.hpp>
using json = nlohmann::json;

class HooksPage {
public:
   struct {
      std::string page;
      std::string single;
   } templates;

   File* configFile;
   json config;

   HooksPage(std::string pageTemplatePath, std::string singleTemplatePath);
   HooksPage();

   bool updateConfigFile();

   int getHookIndex(std::string url);
   void setHook(std::string url);
   void delHook(std::string url);

   std::string getHtml();
};