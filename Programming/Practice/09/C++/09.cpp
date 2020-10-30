#include <iostream>
#include "./../../practice.cpp"

int main () {
	description("Состоится ли встреча дву людей?");

	std::pair<int, int> firstPers;
	std::pair<int, int> secondPers;
	char ch;

	std::cin >> firstPers.first >> ch >> firstPers.second;
	std::cin >> secondPers.first >> ch >> secondPers.second;

	if (firstPers.first < 0 || firstPers.first > 23)
		return 1;

	if (secondPers.first < 0 || secondPers.first > 23)
		return 1;

	if (firstPers.second < 0 || firstPers.second > 59)
		return 1;

	if (secondPers.second < 0 || secondPers.second > 59)
		return 1;

	if (firstPers.first == secondPers.first)
	{
		if (firstPers.second < secondPers.second && secondPers.second <= firstPers.second + 15 ||
			 secondPers.second < firstPers.second && firstPers.second <= secondPers.second + 15)
			std::cout << "Встреча состоится" << std::endl;
		else
			std::cout << "Встреча не состоится" << std::endl;
	}
	else if (firstPers.first > secondPers.first)
	{
		if (60 - firstPers.second + secondPers.second <= 15)
			std::cout << "Встреча состоится" << std::endl;
		else
			std::cout << "Встреча не состоится" << std::endl;
	}
	else if (firstPers.first < secondPers.first)
	{
		if (60 - secondPers.second + firstPers.second <= 15)
			std::cout << "Встреча состоится" << std::endl;
		else
			std::cout << "Встреча не состоится" << std::endl;
	}
	else
		std::cout << "Встреча не состоится" << std::endl;

	return 0;
}
