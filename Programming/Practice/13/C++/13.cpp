#include <iostream>
#include <string.h>
#include "./../../practice.cpp"

int main()
{
	setlocale(LC_ALL, "rus");

	int n;
	std::cin >> n;

	bool *s = new bool[n + 1];
	memset(s, 1, sizeof(s));

	int x = 2;
	while (x * x <= n)
	{
		if (s[x])
			for (int y = x * x; y <= n; y += x)
				s[y] = 0;
		x++;
	}

	if (s[n])
		std::cout << "Простое" << std::endl;
	else
		std::cout << "Составное" << std::endl;

	delete[] s;
	return 0;
}
