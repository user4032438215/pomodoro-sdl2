//settings.cpp 
#include "settings.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool Settings::load(const std::string& path)
{
    std::ifstream ifs(path);

    if (!ifs) {
        return false;
    }

    try {
        const json j = json::parse(ifs);

        const int new_work_minutes =
            j.value("work_minutes", 25);

        const int new_short_break_minutes =
            j.value("short_break_minutes", 5);

        const int new_long_break_minutes =
            j.value("long_break_minutes", 15);

        const int new_long_break_interval =
            j.value("long_break_interval", 4);

        if (new_work_minutes < 1 ||
            new_short_break_minutes < 1 ||
            new_long_break_minutes < 1 ||
            new_long_break_interval < 1) {
            return false;
        }

        // settings.json から 取得した値を代入
        config_.work_minutes =
            new_work_minutes;

        config_.short_break_minutes =
            new_short_break_minutes;

        config_.long_break_minutes =
            new_long_break_minutes;

        config_.long_break_interval =
            new_long_break_interval;


        return true;
    }
    catch (const json::exception&) {
        return false;
    }
}

bool Settings::validate() const noexcept
{
    return 
        config_.work_minutes >= 1 &&
        config_.short_break_minutes >= 1 &&
        config_.long_break_minutes >= 1 &&
        config_.long_break_interval >= 1;
}


//added 261025
bool Settings::apply(const PomodoroConfig& draft) {
    if (!validate_config(draft)) {
        return false;
    }

    config_ = draft;
    return true;
}

bool Settings::save(const std::string& path) const
{
    std::ofstream ofs(path);

    if (!ofs) {
        return false;
    }

    const json j = {
        { "work_minutes", config_.work_minutes },
        { "short_break_minutes", config_.short_break_minutes },
        { "long_break_minutes", config_.long_break_minutes },
        { "long_break_interval", config_.long_break_interval }
    };

    ofs << j.dump(4);

    return static_cast<bool>(ofs);
}

bool Settings::validate_config(
    const PomodoroConfig& config
) const noexcept
{
    return
        config.work_minutes >= 5 &&
        config.work_minutes <= 60 &&
        config.short_break_minutes >= 5 &&
        config.short_break_minutes <= 60 &&
        config.long_break_minutes >= 5 &&
        config.long_break_minutes <= 60 &&
        config.long_break_interval >= 1 &&
        config.long_break_interval <= 10;
}
