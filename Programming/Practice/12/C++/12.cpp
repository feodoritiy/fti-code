#include <iostream>
#include "./../../practice.cpp"

int factorial(int a)
{
	if (a > 1)
		return factorial(a - 1) * a;
	else
		return 1;
}

int main()
{
	description("Факториал на рекурсии");
	int var;
	std::cin >> var;

	std::cout << factorial(var) << std::endl;

	return 0;
}