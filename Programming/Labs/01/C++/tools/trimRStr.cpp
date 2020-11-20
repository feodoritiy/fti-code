#include <string>

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