#include <iostream>
#include "./../../practice.cpp"

int main () {
	description("Консольный оператор с обработкой ошибок.");

	double a, b;
	char oper;

	std::cin >> a >> oper >> b;

	if (oper == '/' && b == 0)
	{
		std::cout << "Íŕ 0 äĺëčňü íĺëüç˙!\n";
		return 0;
	}

	switch (oper)
	{
	case '+':
		std::cout << a + b;
		break;
	case '-':
		std::cout << a - b;
		break;
	case '*':
		std::cout << a * b;
		break;
	case '/':
		std::cout << a / b;
		break;

	default:
		break;
	}

	return 0;
}
