#include "settings.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool Settings::load(const std::string& path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        return false;
    }

    json j;
    ifs >> j;

    work_minutes_ = j.value("work_minutes", 25);
    short_break_minutes_ = j.value("short_break_minutes", 5);
    long_break_minutes_ = j.value("long_break_minutes", 15);
    long_break_interval_ = j.value("long_break_interval", 4);

    return true;
}
