#include <iostream>
#include "./../../practice.cpp"

int main()
{
	description("Разница между присваиванием в int и в double");
	int a = 3, b = 3.14;
	double ad = 3, bd = 3.14;
	std::cout
			<< a << std::endl
			<< b << std::endl
			<< ad << std::endl
			<< bd << std::endl;

	return 0;
}
