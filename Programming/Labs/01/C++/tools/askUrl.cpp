#include <iostream>
#include <string>
#define ASK_URL
#include "./../server.hpp"

#pragma once
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