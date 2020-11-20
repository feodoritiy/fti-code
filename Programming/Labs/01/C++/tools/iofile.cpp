#include <string>
#include <fstream>
#include <sstream>

std::string readFile(const std::string &path)
{
   std::ifstream file(path);
   return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &path, const std::string &data)
{
   std::ofstream file;
   file.open(path);
   file << data;
   file.close();
}