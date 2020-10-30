#include <string>

// api for pretty print
void wl(std::string message) { std::cout << message << std::endl; }
void wl(int message) { std::cout << message << std::endl; }
void wl(double message) { std::cout << message << std::endl; }
void header()
{
  std::setlocale(LC_ALL, "Russian");
  wl("Никонов Фёдор, ПИ-б-о-201(2)");
  wl("----------------------------");
}

void description(std::string message)
{
  header();
  wl("Условие задачи: " + message);
  wl("============================");
}
