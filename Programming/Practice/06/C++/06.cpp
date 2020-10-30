#include <iostream>
#include <math.h>
#include "./../../practice.cpp"

int main () {
	description("Решение линейного уравнения. Введите коэффициенты: a b c");

	double a, b, c;
	std::cin >> a >> b >> c;

	if (a == 0)
	{
		std::cout << -c / b << std::endl;
	}
	else
	{
		double descr = (b * b - 4 * a * c);
		if (descr < 0)
			std::cout << "Корней нет" << std::endl;
		else if (descr == 0)
			std::cout << "x = " << -b / (2 * a) << std::endl;
		else
		{
			descr = sqrt(descr);
			std::cout << "x1 = " << (-b + descr) / (2 * a) << std::endl;
			std::cout << "x2 = " << (-b - descr) / (2 * a) << std::endl;
		}
	}

	return 0;
}
