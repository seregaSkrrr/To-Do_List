#include "Task.h"
#include <filesystem>

void SaveToFile(const std::vector<Task>& tasks, const std::string& FileName) {

	std::ofstream ostream(FileName);
	ostream << tasks.size();

	for (const Task& task : tasks) {
		std::string description = task.description;
		std::replace(description.begin(), description.end(), ' ', '_');
		ostream << std::endl << description << ' ' << task.done;
	}
}

std::vector<Task> LoadTasksFromFile(const std::string& FileName) {

	if (!std::filesystem::exists(FileName)) {
		return std::vector<Task>(); 
	}

	std::vector<Task> tasks;
	std::ifstream istream(FileName, std::ios::app);
	int num;
	istream >> num;

	for (int i{}; i < num; i++) {
		std::string description;
		bool done;
		istream >> description;
		istream >> done;
		std::replace(description.begin(), description.end(), '_', ' ');
		tasks.push_back(Task{ description, done });
	}

	return tasks;
}