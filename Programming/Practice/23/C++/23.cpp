#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "./../../practice.cpp"

#include "./pragma_factorial.cpp"
#include "./ifndef_teilor.cpp"
#include "./ifndef_combine.cpp"

char *table_row(int n)
{
	std::string format = "";
	for (int i = 0; i < n; i++)
		format += "%5s";
	format += "\n";
	char *c_format = new char[format.length()];
	strcpy(c_format, format.c_str());
	return c_format;
}

int main()
{
	printf("%-7s%-7s\n", "n", "n!");
	for (int i = 1; i <= 10; i++)
		printf("%-7d%-7d\n", i, factorial(i));
	printf("\n");

	printf("%-10s%-10s\n", "x", "sin(x)");
	for (double x = 0; x <= M_PI_4 + 0.000005; x += M_PI / 180)
		printf("%-10.5f%-10.5f\n", x, teilor(x, 5));
	printf("\n");

	printf("%-7s%-7s\n", "k", "C(k, 10)");
	for (int k = 1; k <= 10; k++)
		printf("%-7d%-7d\n", k, combine(k, 10));
	printf("\n");

	return 0;
}
