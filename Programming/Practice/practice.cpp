#include <string>

// api for pretty print
void wl(std::string message) { std::cout << message << std::endl; }
void wl(int message) { std::cout << message << std::endl; }
void wl(double message) { std::cout << message << std::endl; }
void header()
{
  wl("Никонов Фёдор, ПИ-б-о-201(2)");
  wl("----------------------------");
}

void description(std::string message)
{
  std::setlocale(LC_ALL, "Russian");
  header();
  wl("Условие задачи: " + message);
  wl("============================");
}
