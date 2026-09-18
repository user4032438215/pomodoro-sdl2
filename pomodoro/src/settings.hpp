// インライン関数使用
#pragma once

#include <string>

class Settings {
public:
    Settings() = default;

    bool load(const std::string& path);

    //bool save(const std::string& path) const; 将来的に実装

    bool validate() const noexcept;

    int work_minutes() const noexcept
    {
        return work_minutes_;
    }

    int short_break_minutes() const noexcept
    {
        return short_break_minutes_;
    }

    int long_break_minutes() const noexcept
    {
        return long_break_minutes_;
    }

    int long_break_interval() const noexcept
    {
        return long_break_interval_;
    }

private:
    int work_minutes_{ 25 };
    int short_break_minutes_{ 5 };
    int long_break_minutes_{ 15 };
    int long_break_interval_{ 4 };
};