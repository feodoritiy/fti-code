#include <iostream>
#include "./../../practice.cpp"

int main()
{
	description("Операции над числами");
	double a, b;
	std::cout << "Введите a и b:\n", std::cin >> a >> b;
	int ai = a, bi = b;

	wl("int : int"), wl(ai + bi), wl(ai - bi), wl(ai * bi), wl(ai / bi);
	wl("dbl : dbl"), wl(a + b), wl(a - b), wl(a * b), wl(a / b);
	wl("int : dbl"), wl(ai + b), wl(ai - b), wl(ai * b), wl(ai / b);
	wl("dbl : int"), wl(a + bi), wl(a - bi), wl(a * bi), wl(a / bi);

	return 0;
}
