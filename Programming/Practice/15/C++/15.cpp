#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include "./../../practice.cpp"

int main () {
	description("frity production 30.10.2020");

START:
	std::srand(time(0));

	int n = rand() % 101;

	int guessing;
	bool showResult = true;

	for (int i = 0; i < 5; i++)
	{
		std::cout << i + 1 << '/' << 5 << ": ";
		std::cin >> guessing;

		if (guessing < n)
			std::cout << "Загаданное число БОЛЬШЕ" << std::endl;
		if (guessing > n)
			std::cout << "Загаданное число Меньше" << std::endl;
		if (guessing == n)
		{
			std::cout << "Поздравляю! Вы угадали" << std::endl;
			showResult = false;
			break;
		}
	}

	if (showResult)
		std::cout << "Вы проиграли. Было загадано число " << n << std::endl;

	int answ = 0;
	std::cout << "Играем снова? (1 - Да): ";
	std::cin >> answ;

	if (answ == 1)
		goto START;

	return 0;
}
