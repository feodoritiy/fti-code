#include <iostream>
#include "./../../practice.cpp"

int main()
{
	description("Падение объекта");

	const double g = 9.8;
	double x0, v0, t;

	std::cout << "x0 v0 t: ", std::cin >> x0 >> v0 >> t;

	double res;
	res = x0 + v0 * t + (g * t * t) / 2;

	std::cout << "res: " << res;

	return 0;
}
