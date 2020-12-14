#include "HooksPage.h"

HooksPage::HooksPage() {
   std::cout << "creating HooksPage Free";
   auto pwd = File::pwd();
   std::cout << pwd;
}

HooksPage::HooksPage(std::string pageTemplatePath, std::string singleTemplatePath) {
   auto pwd = File::pwd();
   auto page = new File(pwd + "/../html" + pageTemplatePath);
   auto single = new File(pwd + "/../html" + singleTemplatePath);
   templates.page = page->read();
   templates.single = single->read();

   configFile = new File(pwd + "/../json/config.json");
   bool exists = configFile->exists();
   if (!exists) {
      configFile->write(R"({ "webhooks": [] })");
   }
   config = configFile->readJson();
}

bool HooksPage::updateConfigFile() {
   return configFile->writeJson(config);
}

int HooksPage::getHookIndex(std::string url) {
   int i = 0;
   for (auto& hook : config["webhooks"]) {
      if (url == hook.get<std::string>()) return i;
      i++;
   }
   return -1;
}
void HooksPage::setHook(std::string url) {
   if (getHookIndex(url) == -1) {
      config["webhooks"].push_back(url);
      updateConfigFile();
   }
}
void HooksPage::delHook(std::string url) {
   int index = getHookIndex(url);
   if (index != -1) {
      config["webhooks"].erase(index);
      updateConfigFile();
   }
}

std::string HooksPage::getHtml() {
   std::string webhooksHtml = "";
   for (auto& hook : config["webhooks"]) {
      webhooksHtml += replaceAll(templates.single, "{Webhook URL}", hook) + "\n";
   }
   std::string resHtml = replaceAll(templates.page, "{webhooks_list}", webhooksHtml);
   return resHtml;
}