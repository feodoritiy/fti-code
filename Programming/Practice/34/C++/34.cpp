#include <iostream>
#include "./../../practice.cpp"

void create(int*& result, int arrayLength, int arrayBegin = 0, int arrayStep = 0) {
	result = new int[arrayLength];

	for (int i = 0, current = arrayBegin; i < arrayLength; i++, current += arrayStep) {
		result[i] = current;
	}
}

void destroy(int*& result) {
	if (result != nullptr) {
		delete[] result;
	}
}

int* sort(int* array, int size) {
	int i, key, j;

	for (i = 1; i < size; i++)
	{
		key = array[i];
		j = i - 1;

		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}

	return array;
}

int* print(int* array, int size) {
	std::cout << "[";
	for (int i = 0; i < size - 1; i++)
		std::cout << array[i] << ", ";
	std::cout << array[size - 1] << "]" << std::endl;
	return array;
}

int main() {
	int size, firstElement, step;
	std::cout << "Array size: ", std::cin >> size;
	std::cout << "First element: ", std::cin >> firstElement;
	std::cout << "Step: ", std::cin >> step;

	int* array;
	create(array, size, firstElement, step);

	sort(array, size);
	print(array, size);

	destroy(array);

	return 0;
}
