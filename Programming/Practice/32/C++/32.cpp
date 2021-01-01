#include <iostream>
#include "./../../practice.cpp"
#include <istream>

#include "csv.hpp"

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

#include <tuple>

struct Passenger {
	bool survival;
	int pclass;
	std::string name;
	std::string sex;
	float age;
	int sibsp;
	int parch;
	std::string ticket;
	float fare;
	std::string cabin;
	std::string embarked;
};

std::istream& operator >> (std::istream& i, std::vector<Passenger>& passengers) {
	csv::CSVReader reader(cwd + "/train.csv");

	for (auto& row : reader) {
		Passenger passenger{
			row["Survived"].get<bool>(),
			row["Pclass"].get<int>(),
			row["Name"].get(),
			row["Sex"].get(),
			(row["Age"].get() != "" ? row["Age"].get<float>() : -1),
			row["SibSp"].get<int>(),
			row["Parch"].get<int>(),
			row["Ticket"].get(),
			row["Fare"].get<float>(),
			row["Cabin"].get(),
			row["Embarked"].get(),
		};
		passengers.push_back(passenger);
	}

	return i;
}

std::ostream& operator << (std::ostream& o, std::vector<Passenger>& passengers) {
	auto writer = csv::make_csv_writer(o);

	writer << std::vector<std::string>{
		"Survived", "Pclass", "Name", "Sex", "Age", "SibSp", "Parch", "Ticket", "Fare", "Cabin", "Embarked"
	};

	for (auto& pass : passengers) {
		writer << std::make_tuple(
			pass.survival,
			pass.pclass,
			pass.name,
			pass.sex,
			pass.age,
			pass.sibsp,
			pass.parch,
			pass.ticket,
			pass.fare,
			pass.cabin,
			pass.embarked
		);
	}

	return o;
}

int main() {

	std::vector<Passenger> passengers;

	std::ifstream data(cwd + "/train.csv");
	if (data.is_open()) {
		data >> passengers;
	}
	else {
		std::cout << "Error opening train.csv" << std::endl;
	}

	sort(passengers.begin(), passengers.end(), [&](Passenger a, Passenger b) { return a.age < b.age; });

	std::vector<Passenger> onlyFemale;
	for (auto& pass : passengers) {
		if (pass.sex == "female" && pass.pclass == 1) {
			onlyFemale.push_back(pass);
		}
	}

	

	std::ofstream output(cwd + "/output.csv");
	if (output.is_open()) {
		output << onlyFemale;
	}
	else {
		std::cout << "Error opening output.csv" << std::endl;
	}

	return 0;
}
