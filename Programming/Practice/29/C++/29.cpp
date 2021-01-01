#include <iostream>
#include "./../../practice.cpp"
#include "./students.cpp"
#define __NO_BOZO_MAIN__
#define __NO_BOZO_COUT__
#include "./../../26/C++/26.cpp"


int main() {
	std::vector<Student> losers;
	for (auto& student : students) {
		if (std::to_string(student.exams["mathematics"]) == "2" ||
			std::to_string(student.exams["physics"]) == "2" ||
			std::to_string(student.exams["history"]) == "2" ||
			std::to_string(student.exams["programming"]) == "2") {
			losers.push_back(student);
		}
	}

	BozoSort(losers);

	if (losers.size() > 0) {
		std::cout << students << std::endl;
		std::cout << losers;
		std::cout << "\nExpulsion" << std::endl << losers[randomInt(losers.size())];
	}
	else {
		std::cout << "Not found";
	}

	return 0;
}
