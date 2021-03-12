#include <iostream>
#include "./../../practice.cpp"

struct IntArray {
	int* data;
	int size;
};

void create(IntArray* arr, int size) {
	arr->data = new int[size];
	arr->size = size;
}
void create(IntArray& arr, int size) {
	arr.data = new int[size];
	arr.size = size;
}

int get(IntArray* arr, int index) {
	return arr->data[index];
}
int get(IntArray& arr, int index) {
	return arr.data[index];
}

void set(IntArray* arr, int index, int value) {
	arr->data[index] = value;
}
void set(IntArray& arr, int index, int value) {
	arr.data[index] = value;
}

void print(IntArray* arr) {
	std::cout << "[";
	for (int i = 0; i < arr->size - 1; i++)
		std::cout << arr->data[i] << ", ";
	std::cout << arr->data[arr->size - 1] << "]" << std::endl;
}
void print(IntArray& arr) {
	std::cout << "[";
	for (int i = 0; i < arr.size - 1; i++)
		std::cout << arr.data[i] << ", ";
	std::cout << arr.data[arr.size - 1] << "]" << std::endl;
}

void resize(IntArray* arr, int newSize) {
	int* newArr = new int[newSize];

	if (newSize < arr->size) {
		for (int i = 0; i < newSize; i++)
			newArr[i] = arr->data[i];
	}
	else { // newSize >= arr->size
		for (int i = 0; i < arr->size; i++)
			newArr[i] = arr->data[i];
		for (int i = arr->size; i < newSize; i++)
			newArr[i] = 0;
	}

	delete arr->data;
	arr->data = newArr;
	arr->size = newSize;
}
void resize(IntArray& arr, int newSize) {
	int* newArr = new int[newSize];

	if (newSize < arr.size) {
		for (int i = 0; i < newSize; i++)
			newArr[i] = arr.data[i];
	}
	else { // newSize >= arr.size
		for (int i = 0; i < arr.size; i++)
			newArr[i] = arr.data[i];
		for (int i = arr.size; i < newSize; i++)
			newArr[i] = 0;
	}

	delete arr.data;
	arr.data = newArr;
	arr.size = newSize;
}

void destroy(IntArray* arr) {
	if (!arr->size) return;
	delete arr->data;
	arr->data = nullptr;
	arr->size = 0;
}
void destroy(IntArray& arr) {
	if (!arr.size) return;
	delete arr.data;
	arr.data = nullptr;
	arr.size = 0;
}

int main() {

	IntArray arr;
	create(arr, 30);

	for (int i = 0; i < arr.size; i++)
		set(arr, i, i + 1);

	print(arr);

	resize(arr, 50);
	print(arr);

	resize(arr, 10);
	print(arr);

	destroy(arr);

	return 0;
}
