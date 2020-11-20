#include "./../server.hpp"

extern std::string weatherOptStr;
extern Weather *weather;

#pragma once
void weatherUpdate()
{
   askUrl("http://api.openweathermap.org", weatherOptStr, [&](Result &res) {
      auto weatherJson = json::parse(res.value().body);
      auto weatherData = weatherJson["hourly"][0];
      weather = new Weather(weatherData);
   });
}