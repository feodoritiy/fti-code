#include <iostream>
#include "./../../practice.cpp"

int main()
{
	description("Свап переменных с темпом и без");

	int a, b;
	std::cout << "Введите a, b: \n", std::cin >> a >> b;

	int c, d;
	c = a;
	d = b; // refresh values
	wl(c), wl(d);
	c = c + d;
	d = c - d;
	c = c - d;
	wl(c), wl(d);

	c = a;
	d = b; // refresh values
	int temp;
	wl(c), wl(d);
	temp = c;
	c = d;
	d = temp;
	wl(c), wl(d);

	return 0;
}
