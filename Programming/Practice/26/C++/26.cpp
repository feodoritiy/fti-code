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

template <typename T>
void printArr(std::vector<T> a, std::string before = "")
{
	std::cout << before;
	for (auto &it : a)
		std::cout << it << ' ';
	std::cout << std::endl;
}

template <typename T>
std::vector<T> sort(std::vector<T> a, bool isAsc = true)
{
	bool sorted = false; //Считаем что не отсортировано

	while (!sorted)
	{ // two rand elements
		int index1 = randomInt(a.size());
		int index2 = randomInt(a.size());

		// swap
		T temp = a[index2];
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

template <typename T>
void BozoSort(std::vector<T> arr, bool isAsc = true)
{
	printArr(sort(arr, isAsc));
}

template <typename T>
void BozoSort(T a, T b, T c, bool isAsc = true)
{
	std::vector<T> arr{a, b, c};
	printArr(sort(arr, isAsc));
}

template <typename T>
void BozoSort(std::vector<std::vector<T>> arrSquare, bool isAsc = true)
{
	int arrLenSqrt = arrSquare.size();
	std::vector<T> arr;
	for (int i = 0; i < arrLenSqrt; i++)
		for (int j = 0; j < arrLenSqrt; j++)
			arr.push_back(arrSquare[i][j]);
	printArr(sort(arr, isAsc));
}

template <typename T>
struct InputData
{
	std::vector<T> linear;
	std::vector<std::vector<T>> square;
	T int1, int2, int3;
};

template <typename T>
InputData<T> inputArr()
{
	int arrLen;
	std::cout << "Введите длину одномерного массива: ", std::cin >> arrLen;
	int arrLenSqrt = sqrt(arrLen);
	std::string rawArr;
	std::cout << "Введите массив через пробел: ";
	std::vector<T> arr;
	for (int i = 0; i < arrLen; i++)
	{
		T it;
		std::cin >> it;
		arr.push_back(it);
	}

	std::vector<T> linear = arr;
	T int1 = arr[0], int2 = arr[1], int3 = arr[2];
	std::vector<std::vector<T>> square{};
	for (int i = 0; i < arrLenSqrt; i++)
	{
		square.push_back(std::vector<T>{});
		for (int j = 0; j < arrLenSqrt; j++)
			square[i].push_back(linear[i * arrLenSqrt + j]);
	}

	InputData<T> res{linear, square, int1, int2, int3};

	return res;
}

template <typename T>
void sortStuff(InputData<T> data)
{
	BozoSort(data.linear);
	BozoSort(data.linear, false);

	BozoSort(data.square);
	BozoSort(data.square, false);

	BozoSort(data.int1, data.int2, data.int3);
	BozoSort(data.int1, data.int2, data.int3, false);
}

int main()
{
	InputData<double> inputDouble = inputArr<double>();
	InputData<std::string> inputString = inputArr<std::string>();

	sortStuff(inputDouble);
	sortStuff(inputString);

	return 0;
}
