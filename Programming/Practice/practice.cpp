#include <string>
#include <vector>
#include <utility>

// api for pretty print
void wl(std::string message) { std::cout << message << std::endl; }
void wl(int message) { std::cout << message << std::endl; }
void wl(double message) { std::cout << message << std::endl; }

void print(std::string message = "", char end = '\n')
{
  std::cout << message << end;
}
template <typename T>
T input(std::string message = "")
{
  T var;
  std::cout << message << ": ", std::cin >> var;
  return var;
}
std::vector<std::string> split(const std::string &str, const std::string &delim)
{
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do
  {
    pos = str.find(delim, prev);
    if (pos == std::string::npos)
      pos = str.length();
    std::string token = str.substr(prev, pos - prev);
    if (!token.empty())
      tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());
  return tokens;
}

template <typename T>
void printVector(std::vector<T> arr, std::string before = "", std::string delim = " ") {
  std::cout << before;
  for (auto& it : arr)
    std::cout << it << delim;
  //std::cout << std::endl;
}

template <typename T>
std::vector<T> sliceVector(std::vector<T> arr, int startIndex, int endIndex)
{
  size_t len = arr.size();
  if (startIndex < 0)
    startIndex = len + startIndex;
  if (endIndex <= 0)
    endIndex = len + endIndex - 1;

  auto start = arr.begin() + startIndex;
  auto end = arr.begin() + endIndex + 1;

  std::vector<T> result(endIndex - startIndex + 1);
  copy(start, end, result.begin());
  return result;
}

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
