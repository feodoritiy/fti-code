#include <iostream>
#include <ctime>
#include <cstdlib>
#include "./../../practice.cpp"

int main () {
	description("frity production 30.10.2020\n===========================");

START:
	std::srand(time(0));

	int n = rand() * 100 / RAND_MAX;

	int guessing;
	bool showResult = true;
	int crutch = -4;

	for (int i = 0; i < 5; i++)
	{
		std::cin >> guessing;

		if (guessing < n && crutch)
			std::cout << "���������� ����� ������" << std::endl;
		if (guessing > n && crutch)
			std::cout << "���������� ����� ������" << std::endl;
		if (guessing == n && crutch)
		{
			std::cout << "����������! �� �������" << std::endl;
			showResult = false;
			break;
		}

		crutch++;
	}

	if (showResult)
		std::cout << "�� ���������. ���� �������� ����� " << n << std::endl;

	int answ = 0;
	std::cout << "������ �����? (1 - ��): ";
	std::cin >> answ;

	if (answ == 1)
		goto START;

	return 0;
}
