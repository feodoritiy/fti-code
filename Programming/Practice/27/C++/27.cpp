#include <iostream>
#include "./../../practice.cpp"

void pushSort(std::vector<int>& arr, int element) {
	arr.push_back(element);
	// insertion sort part
	int j = arr.size() - 2;
	while (j >= 0 && arr[j] < element)
	{
		arr[j + 1] = arr[j];
		j--;
	}
	arr[j + 1] = element;
}

int main() {

	int N; std::cout << "Введите число сигналов: ", std::cin >> N;
	int signals[N];
	std::vector<int> visible;

	int signal, i, j;

	std::cout << "Массив сигналов: ";
	for (i = 0; i < N; i++) {
		std::cin >> signal;
		signals[i] = signal;
	}

	for (i = 0; i < N; i++) {
		signal = signals[i];
		pushSort(visible, signal);
		size_t visibleLen = visible.size();

		printVector(sliceVector(visible, (visibleLen > 5 ? -5 : 0), 0)); // practice.cpp
		std::cout << std::endl;
	}

	return 0;
}
