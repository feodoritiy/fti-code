#include <iostream>
#include "./../../practice.cpp"

int64_t powerful(int a, int b)
{
	int64_t var = 1;
	int i = 0;

	while (i++ < b)
		var *= a;

	return var;
}

int main () {
	description("Степенная функция своими руками");

	int num, pow;
	std::cin >> num >> pow;

	std::cout << powerful(num, pow) << '\n';

	system("pause");
	return 0;

	return 0;
}
