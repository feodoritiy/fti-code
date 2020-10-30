#include <iostream>
#include "./../../practice.cpp"

int main () {
	description("Уравнение с суммой без циклов");

	int64_t s, l1, r1, l2, r2, x1, x2, lr2, range;
	std::cin >> s >> l1 >> r1 >> l2 >> r2;
	lr2 = r2 - l2;

	x1 = l1;
	x2 = s - x1;

	if (x2 < l2)
	{
		range = l2 - x2;
		if (range >= lr2)
		{
			std::cout << "-1";
			return 0;
		}
		else
		{
			x2 += range;
			x1 -= range;
			std::cout << x1 << " " << x2;
		}
	}
	else if (x2 > r2)
	{
		range = x2 - r2;

		if (range >= lr2)
		{
			std::cout << "-1";
			return 0;
		}
		else
		{
			x2 -= range;
			x1 += range;
			std::cout << x1 << " " << x2;
		}
	}
	else
		std::cout << x1 << " " << x2;

	return 0;
}
