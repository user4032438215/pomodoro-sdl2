#include "settings.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
//#include <C:\dev\pomodoro\pomodoro\external\nlohmann\json.hpp>

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

        // ☆ 検証が終わってからメンバーを更新する
        work_minutes_ = new_work_minutes;
        short_break_minutes_ = new_short_break_minutes;
        long_break_minutes_ = new_long_break_minutes;
        long_break_interval_ = new_long_break_interval;

        return true;
    }
    catch (const json::exception&) {
        return false;
    }
}

bool Settings::validate() const noexcept
{
    return work_minutes_ >= 1 &&
        short_break_minutes_ >= 1 &&
        long_break_minutes_ >= 1 &&
        long_break_interval_ >= 1;
}

// 将来的に実装
//bool Settings::save(const std::string& path) const
//{
//    std::ofstream ofs(path);
//
//    if (!ofs) {
//        return false;
//    }
//
//    const json j = {
//        { "work_minutes", work_minutes_ },
//        { "short_break_minutes", short_break_minutes_ },
//        { "long_break_minutes", long_break_minutes_ },
//        { "long_break_interval", long_break_interval_ }
//    };
//
//    ofs << j.dump(4);
//    return static_cast<bool>(ofs);
//}