#include <iostream>
#include <string>
#include <map>

// readFile
#include <fstream>
#include <sstream>
#include <experimental/filesystem>

#include "./json/single_include/nlohmann/json.hpp"
#include "./../../practice.cpp"

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

class Task
{
public:
	int id;
	int userId;
	std::string title;
	bool completed;

	Task(json data)
	{
		id = data["id"].get<int>();
		userId = data["userId"].get<int>();
		title = data["title"].get<std::string>();
		completed = data["completed"].get<bool>();
	}
};

std::string readFile(const std::string &path)
{
	std::ifstream file(path);
	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &path, const std::string &data)
{
	std::ofstream file;
	file.open(path);
	file << data;
	file.close();
}

int main()
{
	auto cwd = fs::current_path().string();
	auto inputText = readFile(cwd + "/Programming/Practice/24/C++/in.json");
	auto tasks = json::parse(inputText);

	std::map<int, int> results;

	for (auto taskData : tasks)
	{
		//std::cout << taskData;
		//std::cout << task.title << std::endl;
		Task task(taskData);
		if (task.completed)
		{
			auto it = results.find(task.userId);
			if (it != results.end())
				it->second += 1;
			else
				results.insert(std::make_pair(task.userId, 1));
		}
	}

	json output;
	for (auto it = results.begin(); it != results.end(); ++it)
	{
		json single = {
			 {"task_completed", it->second},
			 {"userId", it->first},
		};
		output.push_back(single);
	}

	std::cout << output;
	writeFile(cwd + "/Programming/Practice/24/C++/out.json", output.dump());

	return 0;
}
