#include <iostream>
#include "./../../practice.cpp"

#include <ostream>
#include <vector>
#include <cstdlib> // rand

// file read
#include <fstream>

// File::pwd Linux
#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX
std::string pwd() {
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	const char* path;
	if (count != -1) {
		path = dirname(result);
	}
	return std::string(path);
}
std::string cwd = pwd();

std::ostream& operator << (std::ostream& o, const std::vector<int> vector) {
	o << vector.size() << "\t| ";
	for (auto& el : vector) {
		o << &el << " ";
	}
	return o << "\n";
}

int main() {

	std::vector<int> vector;
	std::ofstream file(cwd + "/data-value.txt");

	if (file.is_open()) {
		for (int i = 0; i < 64; i++) {
			vector.push_back(rand());
			file << vector;
		}
		for (int i = 0; i < 64; i++) {
			vector.pop_back();
			file << vector;
		}

		for (int i = 0; i < 64; i++) {
			vector.push_back(rand());
			file << vector;
		}
		for (int i = 0; i < 64; i++) {
			vector.pop_back();
			file << vector;
		}
	}

	else {
		std::cout << "Error on data.txt open" << std::endl;
	}

	file.close();

	return 0;
}
