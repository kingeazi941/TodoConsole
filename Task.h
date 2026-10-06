#pragma once

#include<string>
#include<optional>

enum class Priority
{
    Low=1,
    Medium=2,
    High=3
};

inline std::string to_string(Priority p)
{
    switch (p) {
    case Priority::Low: return "Low";
    case Priority::Medium: return "Medium";
    case Priority::High: return "High";
    default: return "unknown";
    }
    return "Unknown";
}

struct Task
{
    int id=0;
    std::string title;
    bool done{false};
    Priority priority{Priority::Medium};
    std::optional<std::string> due;
};
