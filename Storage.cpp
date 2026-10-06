#include "Storage.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<Task> Storage::load(const std::string &filename)
{
    std::vector<Task> tasks;
    std::ifstream file(filename);

    if(!file) return tasks;
    std::string line;
    while(std::getline(file,line))
    {
        if(line.empty()){continue;}

        std::istringstream iss(line);
        std::string token;
        Task t;

        if(!std::getline(iss,token,'|')) continue;
        t.id=std::stoi(token);

        if(!std::getline(iss,token,'|')) continue;
        t.done=(token=="1");

        if(!std::getline(iss,token,'|')) continue;
        t.priority=static_cast<Priority>(std::stoi(token));

        if(!std::getline(iss,token,'|')) continue;
        t.title=token;

        if(std::getline(iss,token,'|') && !token.empty())
        {
            t.due=token;
        }
        tasks.push_back(std::move(t));
    }
    return tasks;
}

void Storage::save(const std::string &filename, const std::vector<Task> &tasks)
{
    std::ofstream file(filename);
    if(!file){
        std::cerr<<"Could not save file";
        return;
    }

    for(const auto& t: tasks)
    {
        file << t.id <<'|'
             <<(t.done ? 1:0)<< '|'
             <<static_cast<int>(t.priority)<<'|'
             <<t.title<<'|';
        if(t.due)
        {
            file<<*t.due;
        }
        file<<'\n';
    }
}

int Storage::next_id(const std::vector<Task> &tasks)
{
    if(tasks.empty()) return 1;

    int max_id=0;
    for(const auto& t : tasks)
    {
        if(t.id > max_id)
        {
            max_id=t.id;
        }
    }
    return max_id+1;
}