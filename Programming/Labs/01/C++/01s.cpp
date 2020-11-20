#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "./include/cpp_httplib/httplib.h"
using namespace httplib;

#include "./include/json/json.hpp"
using json = nlohmann::json;

#include <vector>
#include <string>

#include <fstream>
#include <sstream>

// -------
// <TOOLS>
// -------

// Weather.cpp
class Weather
{
public:
   int temp;
   std::string descr;
   std::string icon;
   Weather() {}
   Weather(json weatherData)
   {
      temp = (int)weatherData["temp"].get<float>();
      descr = weatherData["weather"][0]["description"].get<std::string>();
      icon = weatherData["weather"][0]["icon"].get<std::string>();
   }

   static std::string options()
   {
      const std::string weatherKey = "c59cd208b47baa4b871e2d31b36ea921";
      std::vector<std::string> weatherOpt{
          "lat=44.95719",
          "lon=34.11079",
          "exclude=current,minutely,daily,alerts",
          "units=metric",
          "lang=ru",
          "appid=" + weatherKey};

      std::string weatherOptStr = "";
      for (auto optPart : weatherOpt)
         weatherOptStr += "&" + optPart;
      weatherOptStr = "/data/2.5/onecall?" + weatherOptStr.substr(1);
      return weatherOptStr;
   }
};
std::string weatherOptStr;
std::string weatherWidget;
int prevtime;
Server server;
Weather *weather;

// askUrl.cpp
void askUrl(std::string domain, std::string path, std::function<void(Result &)> okCallback)
{
   Headers headers = {{"Accept-Encoding", "gzip, deflate"}};
   printf("\nAsking %s%s\n", domain.c_str(), path.c_str());
   Client client(domain.c_str());
   auto res = client.Get(path.c_str(), headers);
   if (res)
   {
      if (res->status == 200)
         okCallback(res);
      else
         std::cout << "Error. Status code: " << res->status << std::endl;
   }
   else
      std::cout << "Error. On result execute, error code: " << res.error() << std::endl;
}

// iofile.cpp
std::string readFile(const std::string &path)
{
   std::ifstream file(path);
   return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &path, const std::string &data)
{
   std::ofstream file;
   file.open(path);
   file << data;
   file.close();
}

// replaceAll.cpp
std::string replaceAll(std::string str, const std::string &from, const std::string &to)
{
   size_t start_pos = 0;
   while ((start_pos = str.find(from, start_pos)) != std::string::npos)
   {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
   }
   return str;
}

// timeCheck.cpp
int needUpdateByTime(int prevtime, int unixtime)
{
   int unixHours = unixtime / 3600, prevHours = prevtime / 3600;
   return unixHours - 1 >= prevHours;
}

extern int prevtime;

bool needNewWeather()
{
   bool needNew = false;
   askUrl("http://worldtimeapi.org", "/api/timezone/Europe/Simferopol", [&](Result &res) {
      auto timeJson = json::parse(res->body);
      auto unixtime = timeJson["unixtime"].get<int>();

      printf("unixtime(%d) %s prevtime(%d)\n", unixtime, (unixtime > prevtime ? ">" : "<"), prevtime);

      needNew = unixtime && needUpdateByTime(prevtime, unixtime);
      prevtime = unixtime;
   });

   return needNew;
}

//trimRStr.cpp
std::string trimRStr(std::string str, std::string ch)
{
   int len = str.length();
   std::string rch = str.substr(len - 1);
   while (rch == ch)
   {
      str = str.substr(0, len - 1);
      len--;
      rch = str.substr(len - 1);
   }

   return str;
}

// weatherUpdate.cpp
void weatherUpdate()
{
   askUrl("http://api.openweathermap.org", weatherOptStr, [&](Result &res) {
      auto weatherJson = json::parse(res.value().body);
      auto weatherData = weatherJson["hourly"][0];
      weather = new Weather(weatherData);
   });
}

// --------
// </TOOLS>
// --------

// --------
// <ROTES>
// --------

// root.cpp
void rootRoteHandler(const Request &req, Response &res)
{
   if (needNewWeather())
      weatherUpdate();
   else
      std::cout << "Weather update skip, cash is OK." << std::endl;

   std::cout << std::endl
             << "descr: " << (weather->descr) << std::endl
             << "temp: " << (weather->temp) << std::endl;

   std::string responseHtml = weatherWidget;
   std::map<std::string, std::string> replacements = {
       {"{{description}}", (weather->descr)},
       {"{{temp}}", trimRStr(trimRStr(std::to_string(weather->temp), "0"), ".")},
       {"{{icon}}", (weather->icon)},
   };

   for (auto const &[from, to] : replacements)
      responseHtml = replaceAll(responseHtml, from, to);

   res.set_content(responseHtml.c_str(), "text/html");
}

// raw.cpp
void rawRoteHandler(const Request &req, Response &res)
{
   if (needNewWeather())
      weatherUpdate();
   else
      std::cout << "Weather RAW update skip, cash is OK." << std::endl;

   std::cout << std::endl
             << "descr: " << (weather->descr) << std::endl
             << "temp: " << (weather->temp) << std::endl;

   res.set_content(json{{"temp", (weather->temp)}, {"descr", (weather->descr)}}.dump(), "text/json; charset=UTF-8");
}

// --------
// </ROTES>
// --------

int main()
{
   // running on repo root
   auto cwd = fs::current_path().string();

   weatherOptStr = Weather::options();
   prevtime = 0;
   weatherWidget = readFile(cwd + "/Programming/Labs/01/C++/widget.html");

   server.Get("/", rootRoteHandler);
   server.Get("/raw", rawRoteHandler);

   // STARTING SERVER
   std::cout << "Server served on localhost:3000\n";
   server.listen("localhost", 3000);

   return 0;
}