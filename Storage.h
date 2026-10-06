#pragma once

#include "Task.h"
#include <vector>
#include <string>

class Storage{
public:
    static std::vector<Task> load(const std::string& filename);
    static void save(const std::string& filename, const std::vector<Task>& tasks);
    static int next_id(const std::vector<Task>& tasks);
};
