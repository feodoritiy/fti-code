#include <iostream>
#include "./../../practice.cpp"

int main()
{
	int num;
	std::cin >> num;

	if (num == 0)
		return 0;

	int var = 2;
	int i = 1;

	while (var < num)
	{
		var *= 2;
		i++;
	}

	std::cout << i << std::endl;

	return 0;
}