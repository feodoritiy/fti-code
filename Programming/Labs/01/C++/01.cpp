#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "./server.hpp"

#include "./tools/Weather.cpp"
#include "./tools/iofile.cpp"

std::string weatherOptStr;
std::string weatherWidget;
int prevtime;
Server server;
Weather *weather;

#include "./rotes/root.cpp"
#include "./rotes/raw.cpp"

// api key: c59cd208b47baa4b871e2d31b36ea921
// wea: https://api.openweathermap.org/data/2.5/onecall?lat=44.95719&lon=34.11079&exclude=current,minutely,daily,alerts&units=metric&lang=ru&appid=c59cd208b47baa4b871e2d31b36ea921
// ico: https://openweathermap.org/themes/openweathermap/assets/vendor/owm/img/widgets/03n.png
// time: http://worldtimeapi.org/api/timezone/Europe/Simferopol

int main()
{
	auto cwd = fs::current_path().string();

	weatherOptStr = Weather::options();
	prevtime = 0;
	weatherWidget = readFile(cwd + "/Programming/Labs/01/C++/widget.html");

	server.Get("/", rootRoteHandler);
	server.Get("/raw", rawRoteHandler);

	// STARTING SERVER
	std::cout << "Server served on localhost:3000\n";
	server.listen("localhost", 3000);

	return 0;
}
