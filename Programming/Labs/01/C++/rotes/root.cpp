#include "./../server.hpp"
#include "./../tools/replaceAll.cpp"
#include "./../tools/trimRStr.cpp"
#include "./../tools/timeCheck.cpp"
#include "./../tools/weatherUpdate.cpp"

extern std::string weatherOptStr;
extern Weather *weather;
extern int prevtime;
extern std::string weatherWidget;

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