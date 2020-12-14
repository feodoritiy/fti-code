#include "root.h"

namespace RouteRoot {

   std::string dialog(std::string dialogName, json state, json config) {
      std::string targetJsonString = File::Read(DIALOGS_JSON_PATH + "/" + dialogName);
      json targetDialog = json::parse(targetJsonString);
      bool notStartup = state != nullptr;

      std::cout << "Taking dialog: " << dialogName << std::endl;

      if (notStartup) { // not startup
         if (config.contains("buttons")) { // generate buttons
            auto buttons = config["buttons"].get<std::string>();

            if (buttons == "speak") { // speak buttons
               if (!state["speak"].get<bool>()) {
                  //targetDialog["parameters"] = R"({
                  //   "instance": "mute"
                  //})"_json;
                  //targetDialog["response"]["tts"] = nullptr;
                  targetDialog["response"].erase("tts");
                  targetDialog["response"]["buttons"].push_back(R"({ "title": "Говорить" })"_json);
               }
               else {
                  targetDialog["response"]["buttons"].push_back(R"({ "title": "Молчать" })"_json);
               }
               targetDialog["response"]["buttons"].push_back(R"({ "title": "Корзина" })"_json);
            } // speak buttons
            else if (buttons == "cart") { // cart buttons
               json buttonsCart = R"([
               { "title": "Очистить корзину" },
               { "title": "Добавить в корзину" },
               { "title": "Удалить из корзины" },
               { "title": "Что в корзине" },
               { "title": "Сумма" },
               { "title": "Покупка завершена" }
            ])"_json;

               for (auto& button : buttonsCart) {
                  targetDialog["response"]["buttons"].push_back(button);
               }
            } // cart buttons
         } // generate buttons

         if (config.contains("help_all_name")) { // single help
            std::string helpText, helpTts;
            auto helpName = config["help_all_name"].get<std::string>();

            auto helpArr = json::parse(targetDialog["help_arr"].dump());
            targetDialog.erase("help_arr");

            for (auto it = helpArr.begin(); it != helpArr.end(); ++it) {
               json helpCurr = *it;
               auto helpNameCurr = helpCurr["name"].get<std::string>();
               if (helpNameCurr == helpName) {
                  helpText = helpCurr["text"].get<std::string>();
                  helpTts = helpCurr["tts"].get<std::string>();
                  break;
               }
            }

            std::cout << "help.text: " << helpText << std::endl;
            std::cout << "help.tts: " << helpTts << std::endl;
            targetDialog["response"]["text"] = helpText;
            targetDialog["response"]["tts"] = helpTts;
         } // single help

         if (config.contains("text")) { // use custom text
            auto newText = config["text"].get<std::string>();
            targetDialog["response"]["text"] = newText;
            targetDialog["response"]["tts"] = newText;
         } // use custom text

         targetDialog["session_state"] = state;
      } // not startup
      else { // is startup
         state = R"({
            "speak": true,
            "cart": [],
            "mode": "normal"
         })"_json;

         targetDialog["response"]["buttons"].push_back(R"({ "title": "Молчать" })"_json);
         targetDialog["session_state"] = state;
      } // is startup

      return targetDialog.dump();
   }

   void Handler(const Request& req, Response& res)
   {
      std::cout << "------------------------" << std::endl;

      std::string response;
      auto yandexJson = json::parse(req.body);

      // if new session
      if (yandexJson["session"]["new"].get<bool>()) {
         response = dialog("startup.json", nullptr);
      }
      else { // session continue
         auto state = yandexJson["state"]["session"];

         std::string command = getCommand(yandexJson);
         std::cout << "\nКоманда: " << command << std::endl;
         std::string commandOrig = yandexJson["request"]["original_utterance"].get<std::string>();
         std::cout << "Команда (ориг): " << commandOrig << "\n" << std::endl;

         if (!(state.contains("cart") && state.contains("speak") && state.contains("mode"))) {
            response = dialog("error.json", state);
         }
         else { // is correct session data
            auto cart = state["cart"];
            auto speak = state["speak"];
            auto mode = state["mode"];

            bool isWait = state.contains("wait") && !state["wait"].is_null();
            std::string wait = isWait ? state["wait"].get<std::string>() : "";

            auto buttonsNormal = R"({ 
               "buttons": "speak"
            })"_json;
            auto buttonsCart = R"({ 
               "buttons": "cart"
            })"_json;

            int tokensCount = yandexJson["request"]["nlu"]["tokens"].size();

            if (mode == "normal") { // mode: normal
               if (false) {
               }
               else if (command == "молчать") {
                  state["speak"] = false;
                  response = dialog("mode/silent.json", state, buttonsNormal);
               }
               else if (command == "говорить") {
                  state["speak"] = true;
                  response = dialog("mode/speak.json", state, buttonsNormal);
               }
               else if (command == "помощь") {
                  state["mode"] = "help";
                  response = dialog("help/start.json", state);
               }
               else if (command == "корзина") {
                  state["mode"] = "cart";
                  response = dialog("cart/start.json", state, buttonsCart);
               }
               else {
                  response = dialog("unknown.json", state, buttonsNormal);
               }
            } // mode: normal


            else if (mode == "help") { // mode: help
               if (command == "назад") {
                  state["mode"] = "normal";
                  response = dialog("help/end.json", state, buttonsNormal);
               }
               else {
                  response = dialog("help/all.json", state, json::parse("{ \"help_all_name\": \"" + commandOrig + "\" }"));
               }
            } // mode: help


            else if (mode == "cart") { // mode: cart
               if (false) {
               }

               else if (command == "очистить корзину") {
                  state["cart"] = json::array();
                  response = dialog("cart/skill/clean.json", state, buttonsCart);
               }

               else if ((isWait && wait == "добавить в корзину") || command.rfind("добавить в корзину", 0) == 0) { // command starts with ...
                  if (!isWait) { // nothing to wait
                     if (tokensCount == 3) { // no args given
                        state["wait"] = "добавить в корзину";
                        response = dialog("cart/skill/add_no_args.json", state);
                     } // no args given
                     else { // args given
                        json productData = getProductSet(yandexJson, 3);
                        state["cart"].push_back(productData);
                        response = dialog("cart/skill/add.json", state, buttonsCart);
                     } // args given
                  } // nothin to wait
                  else { // was waiting
                     state["wait"] = nullptr;

                     json productData = getProductSet(yandexJson, 0);
                     state["cart"].push_back(productData);
                     response = dialog("cart/skill/add.json", state, buttonsCart);
                  } // was waiting
               }

               else if ((isWait && wait == "удалить из корзины") || command.rfind("удалить из корзины", 0) == 0) {
                  if (!isWait) { // nothing to wait
                     if (tokensCount == 3) { // no args given
                        state["wait"] = "удалить из корзины";
                        response = dialog("cart/skill/remove_no_args.json", state);
                     } // no args given
                     else { // args given
                        removeProduct(3, yandexJson, state);
                        response = dialog("cart/skill/remove.json", state, buttonsCart);
                     } // args given
                  } // nothin to wait
                  else { // was waiting
                     state["wait"] = nullptr;
                     removeProduct(0, yandexJson, state);
                     response = dialog("cart/skill/remove.json", state, buttonsCart);
                  } // was waiting
               }

               else if (command == "что в корзине") {
                  auto cart = state["cart"];

                  if (cart.empty()) response = dialog("cart/skill/list_free.json", state, buttonsCart);
                  else {
                     std::string cartText = "Ща по фактам раскидаю: ";
                     for (auto& product : cart) {
                        auto name = product["name"].get<std::string>();
                        int priceVal = product["price"].get<int>();
                        auto price = std::to_string(priceVal);
                        cartText += name + " на " + price + " " + rubleString(priceVal) + ", ";
                     }
                     json configList = {
                        { "text", cartText },
                        { "buttons", "cart" },
                     };
                     response = dialog("cart/skill/list.json", state, configList);
                  }
               }

               else if (command == "сумма") {
                  int cartSum = 0;
                  for (auto& product : state["cart"]) {
                     cartSum += product["price"].get<int>();
                  }

                  json configSum = {
                        { "text", "Товаров на " + std::to_string(cartSum) + " " + rubleString(cartSum) },
                        { "buttons", "cart" },
                  };
                  response = dialog("cart/skill/sum.json", state, configSum);
               }

               else if (command == "покупка завершена") {
                  std::string id = yandexJson["session"]["user"].contains("user_id")
                     ? yandexJson["session"]["user"]["user_id"].get<std::string>()
                     : "anonymous";
                  json check = {
                     {"user_id", id},
                     {"check", state["cart"]},
                  };

                  std::string checkString = check.dump();
                  std::cout << "Check data:" << checkString << std::endl;

                  for (auto& hook : webhooksPage.config["webhooks"]) {
                     std::string hookString = hook.get<std::string>();
                     std::cout << "Check send: " << hookString << std::endl;
                     Client sender{ hookString.c_str() };

                     sender.Post("/", checkString, "application/json; charset=utf8");
                  }

                  state["mode"] = "normal";
                  response = dialog("cart/end.json", state, buttonsNormal);
               }

               else {
                  response = dialog("unknown.json", state, buttonsCart);
               }
            } // mode: cart
         } // is correct session data
      } // session continue

      std::cout << req.body.c_str() << std::endl;
      res.set_content(response, "text/json; charset=UTF-8");
   }

   std::string getCommand(json yandexJson) { // take command from command prop or nlu list
      std::string command;
      if (yandexJson["request"].contains("command")) {
         command = yandexJson["request"]["command"].get<std::string>();
      }
      else {
         command = "";
         for (auto& token : yandexJson["request"]["nlu"]) {
            command += token.get<std::string>();
         }
      }
      return command;
   }

   std::string getProductName(json yandexJson, int productTokenIndex) {
      return yandexJson["request"]["nlu"]["tokens"][productTokenIndex].get<std::string>();
   }

   json getProductSet(json yandexJson, int productTokenIndex) {
      std::string productName = getProductName(yandexJson, productTokenIndex);

      json entities = yandexJson["request"]["nlu"]["entities"];
      int productPrice;
      for (auto it = entities.begin(); it != entities.end(); ++it) {
         if ((*it)["type"] == "YANDEX.NUMBER") {
            productPrice = (*it)["value"].get<int>();
            break;
         }
      }

      std::cout << "product.name: " << productName << std::endl;
      std::cout << "product.price: " << productPrice << std::endl;

      auto res = json{
         {"name", productName},
         {"price", productPrice},
      };
      return res;
   }

   void removeProduct(int productTokenIndex, json& yandexJson, json& state) {
      json newCart = json::array();

      std::string productName = getProductName(yandexJson, productTokenIndex);
      int i = 0;
      for (auto& product : state["cart"]) {
         std::string productNameCurr = product["name"].get<std::string>();
         if (productName != productNameCurr) {
            newCart.push_back(product);
         }
         i++;
      }

      state["cart"] = newCart;
   }

   std::string rubleString(int number) {
      switch (number % 100)
      {
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19: return "рублей"; break;
      default:
         switch (number % 10)
         {
         case 0: return "рублей"; break;
         case 1: return "рубль"; break;
         case 2:
         case 3:
         case 4: return "рубля"; break;
         case 5:
         case 6:
         case 7:
         case 8:
         case 9: return "рублей"; break;
         default: std::cout << "Ошибка rubleString, введите положительное число!"; break;
         }
      }
      return "Ошибка";
   }

} // namespace RouteRoot