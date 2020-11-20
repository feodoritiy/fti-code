#include "./../server.hpp"
#include "./../tools/timeCheck.cpp"
#include "./../tools/weatherUpdate.cpp"

extern std::string weatherOptStr;
extern Weather *weather;
extern int prevtime;

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