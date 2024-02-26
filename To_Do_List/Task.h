#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <fstream>

struct Task {
	std::string description;
	bool done;

};

void SaveToFile(const std::vector<Task>& tasks, const std::string& FileName);
std::vector<Task> LoadTasksFromFile(const std::string& FileName);