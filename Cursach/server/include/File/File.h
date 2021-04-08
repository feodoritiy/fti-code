#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <json/json.hpp>
using json = nlohmann::json;

// File::pwd Linux
#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX

class File {
public:
   std::string abspath;

   static std::string pwd();

   static std::string Read(std::string path);
   static void Write(std::string path, std::string data);
   static json ReadJson(std::string path);
   static void WriteJson(std::string path, json data);

   File(std::string abspathToFile);

   std::string read();
   void write(const std::string& data);
   json readJson();
   void writeJson(json data);

   bool exists();
};