#ifndef WEATHER_CLASS
#define WEATHER_CLASS

#include <string>
#include <vector>
#include "./../json.hpp"

class Weather
{
public:
   float temp;
   std::string descr;
   std::string icon;
   Weather() {}
   Weather(json weatherData)
   {
      temp = weatherData["temp"].get<float>();
      //std::cout << weatherData.find("weather").value().begin().value();
      //std::cout << weatherData["weather"]["0"];
      //std::cout << weatherData["weather"]["0"]["description"];
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

#endif