#pragma once

#include "webhooks.h"

void webhooksRoteHandler(const Request& req, Response& res)
{
   if (req.has_param("del")) {
      auto val = req.get_param_value("del");
      webhooksPage.delHook(val);
   }
   else if (req.has_param("set")) {
      auto val = req.get_param_value("set");
      webhooksPage.setHook(val);
   }

   std::cout << "Req: " << req.body.c_str() << std::endl;
   res.set_content(webhooksPage.getHtml(), "text/html; charset=UTF-8");
}