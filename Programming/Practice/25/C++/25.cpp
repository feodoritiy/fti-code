#include <iostream>
#include "./../../practice.cpp"
#include <cstdlib>
#include <vector>
#include <cmath>

int randomInt(int range)
{
	int rawResult;
	rawResult = std::rand();
	return rawResult % range;
}

void printArr(std::vector<int> a, std::string before = "")
{
	std::cout << before;
	for (auto &it : a)
		std::cout << it << ' ';
	std::cout << std::endl;
}

std::vector<int> sort(std::vector<int> a, bool isAsc = true)
{
	bool sorted = false; //Считаем что не отсортировано

	while (!sorted)
	{ // two rand elements
		int index1 = randomInt(a.size());
		int index2 = randomInt(a.size());

		// swap
		int temp = a[index2];
		a[index2] = a[index1];
		a[index1] = temp;

		// check sorted
		sorted = true;
		for (int i = 1; i < a.size(); i++)
			if (isAsc ? (a[i - 1] > a[i]) : (a[i - 1] < a[i]))
			{ // if sequence bad break and False
				sorted = false;
				break;
			}
	}

	return a;
}

void BozoSort(std::vector<int> arr, bool isAsc = true)
{
	printArr(sort(arr, isAsc));
}

void BozoSort(int a, int b, int c, bool isAsc = true)
{
	std::vector<int> arr{a, b, c};
	printArr(sort(arr, isAsc));
}

void BozoSort(std::vector<std::vector<int>> arrSquare, bool isAsc = true)
{
	int arrLenSqrt = arrSquare.size();
	std::vector<int> arr;
	for (int i = 0; i < arrLenSqrt; i++)
		for (int j = 0; j < arrLenSqrt; j++)
			arr.push_back(arrSquare[i][j]);
	printArr(sort(arr, isAsc));
}

int main()
{
	int arrLen;
	std::cout << "Введите длину одномерного массива: ", std::cin >> arrLen;
	int arrLenSqrt = sqrt(arrLen);
	std::string rawArr;
	std::cout << "Введите массив через пробел: ";
	std::cin.ignore();
	std::getline(std::cin, rawArr);
	auto arrStr = split(rawArr, " ");

	std::vector<int> arr = {};
	for (auto &it : arrStr)
		arr.push_back(std::stoi(it));

	std::vector<int> linear = arr;
	int int1 = arr[0], int2 = arr[1], int3 = arr[2];
	std::vector<std::vector<int>> square{};
	for (int i = 0; i < arrLenSqrt; i++)
	{
		square.push_back(std::vector<int>{});
		for (int j = 0; j < arrLenSqrt; j++)
			square[i].push_back(linear[i * arrLenSqrt + j]);
	}

	BozoSort(linear);
	BozoSort(linear, false);

	BozoSort(square);
	BozoSort(square, false);

	BozoSort(int1, int2, int3);
	BozoSort(int1, int2, int3, false);

	return 0;
}
