#include <iostream>
#include "./../../practice.cpp"
#include "./LootBox.cpp"

// lowercase
#include <algorithm>
#include <cctype>


int main () {
	while (true) {
		std::cout << "\nОткрыть лутбокс? Yes/No" << std::endl;
		std::string answ; std::cin >> answ;
		// lower case
		std::transform(answ.begin(), answ.end(), answ.begin(), [](unsigned char c) { return std::tolower(c); });

		if (answ == "y" || answ == "yes") {
			std::cout << generateLootBox();
		}
		else if (answ == "n" || answ == "no")
			break;
		else
			continue;
	}
	
	return 0;
}
