#include "File.h"

// static

std::string File::pwd() {
   char result[PATH_MAX];
   ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
   const char* path;
   if (count != -1) {
      path = dirname(result);
   }
   return std::string(path);
}

std::string File::Read(std::string path) {
   File* f = new File(path);
   return f->read();
}
void File::Write(std::string path, std::string data) {
   File* f = new File(path);
   f->write(data);
}

json File::ReadJson(std::string path) {
   File* f = new File(path);
   return f->readJson();
}
void File::WriteJson(std::string path, json data) {
   File* f = new File(path);
   f->writeJson(data);
}


// constructors

File::File(std::string abspathToFile) {
   abspath = abspathToFile;
}


// methods

std::string File::read() {
   std::string res;
   std::ifstream file(abspath);
   if (file.good()) {
      res = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();
      return res;
   }
   else {
      file.close();
      std::cout << "File::read Error: file ifstream is bad.";
      throw "File::read Error: file ifstream is bad.";
   }
}
void File::write(const std::string& data) {
   std::ofstream file;
   file.open(abspath);
   file << data;
   file.close();
}

json File::readJson() {
   return json::parse(read());
}
void File::writeJson(json data) {
   write(data.dump());
}

bool File::exists() {
   std::ifstream file(abspath);
   bool res = file.good();
   file.close();
   return res;
}