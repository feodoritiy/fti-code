#include "./../server.hpp"
#include "./askUrl.cpp"

#pragma once

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