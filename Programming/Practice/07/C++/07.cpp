#include <iostream>
#include <math.h>
#include "./../../practice.cpp"

int main () {
	// Площадь треугольника:
	// 1. по 3 точкам
	// 2. по 3 сторонам
	description("Площадь треугольника по: \n1. трем точкам \n2. трем сторонам");
	int choice = 0;
	std::cin >> choice;

	if (choice == 2)
	{
		// по сторонам
		double a, b, c;
		std::cin >> a >> b >> c;

		double p = (a + b + c) / 2;

		std::cout << "S = " << sqrt(p * (p - a) * (p - b) * (p - c)) << '\n';
	}
	else if (choice == 1)
	{
		// по координатам

		double ax, ay, bx, by, cx, cy;

		std::cin >> ax >> ay;
		std::cin >> bx >> by;
		std::cin >> cx >> cy;

		double ab_vec_x, ab_vec_y, ab;
		ab_vec_x = bx - ax;
		ab_vec_y = by - ay;
		ab = sqrt(ab_vec_x * ab_vec_x + ab_vec_y * ab_vec_y);

		double ac_vec_x, ac_vec_y, ac;
		ac_vec_x = cx - ax;
		ac_vec_y = cy - ay;
		ac = sqrt(ac_vec_x * ac_vec_x + ac_vec_y * ac_vec_y);

		double bc_vec_x, bc_vec_y, bc;
		bc_vec_x = cx - bx;
		bc_vec_y = cy - by;
		bc = sqrt(bc_vec_x * bc_vec_x + bc_vec_y * bc_vec_y);

		double p = (ab + ac + bc) / 2;

		double s = sqrt(p * (p - ab) * (p - ac) * (p - bc));

		std::cout << "S = " << s;
	}
	else
	{
		std::cout << "Такой режим ввода координат не определён!\n";
		return 1;
	}

	return 0;
}
