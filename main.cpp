#include "Storage.h"
#include "Task.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

void print_task(const Task& t)
{
    std::string status=t.done ? "[x]" : "[ ]";
    std::string due=t.due ? *t.due : "-";

    std::cout <<t.id<<" "<<status<<" "
              <<to_string(t.priority)<<" "
              <<due<<" "
              <<t.title<<'\n';
}

void list_tasks(const std::vector<Task>& tasks, const std::string& filter="all")
{
    bool found=false;
    for(const auto& t: tasks)
    {
        if(filter == "pending" && t.done) continue;
        if(filter == "done" && !t.done) continue;
        if(filter == "high" && t.priority != Priority::High) continue;

        print_task(t);
        found=true;
    }
    if(!found)
    {
        std::cout<<"No task found.\n";
    }
}

void show_menu()
{
    std::cout << "\n=== Simple Todo (Console) ===\n"
              << "1. List all\n"
              << "2. List pending\n"
              << "3. List high priority\n"
              << "4. Add task\n"
              << "5. Mark complete\n"
              << "6. Delete task\n"
              << "7. Save & Quit\n"
              << "Choice: ";
}


int main(int argc, char *argv[])
{
    const std::string filename="tasks.txt";
    std::vector<Task> tasks= Storage::load(filename);
    std::cout<<"Loaded "<<tasks.size()<<"task.\n";

    bool running=true;
    while(running)
    {
        show_menu();
        int choice;
        if(!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Invalid input\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        switch(choice)
        {
        case 1: list_tasks(tasks,"all");break;
        case 2: list_tasks(tasks,"pending");break;
        case 3: list_tasks(tasks,"high");break;

        case 4:{
            Task t;
            t.id=Storage::next_id(tasks);

            std::cout<<"Title: ";
            std::getline(std::cin,t.title);
            if(t.title.empty())
            {
                std::cout<<"Title cannot be empty";
                break;
            }
            std::cout<<"Priority (1=Low, 2=Medium, 3=High): ";
            int p;
            std::cin>>p;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if(p>=1 && p<=3)
            {
                t.priority=static_cast<Priority>(p);
            }

            std::cout<<"Due date (YYYY-MM-DD) or empty: ";
            std::string due;
            std::getline(std::cin,due);
            if(!due.empty())
            {
                t.due=due;
            }

            tasks.push_back(std::move(t));
            std::cout<<"Task added\n";
            break;
        }
        case 5:{
            std::cout<<"Task ID: ";
            int id;
            std::cin>>id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            auto it=std::find_if(tasks.begin(),tasks.end(),
                                   [id](const Task& t){return t.id== id;});

            if(it != tasks.end())
            {
                it->done=true;
                std::cout <<"Marked complete\n";
            }else{
                std::cout<<"Not found\n";
            }
            break;
        }
        case 6:{
            std::cout<<"Task ID to delete: ";
            int id;
            std::cin>>id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            auto it=std::find_if(tasks.begin(),tasks.end(),
                                   [id](const Task& t){return t.id== id;});
            if(it != tasks.end()){
                tasks.erase(it);
                std::cout<<"Deleted\n";
            }else{
                std::cout<<"Not found\n";
            }
            break;
        }
        case 7:
            Storage::save(filename,tasks);
            std::cout<<"Saved. Bye!\n";
            running=false;
            break;

        default:
            std::cout<<"Unknown choice\n";
        }
    }
    return 0;
}
