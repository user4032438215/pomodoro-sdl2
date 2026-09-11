#pragma once
#include <string>

class Settings {
public:
    bool load(const std::string& path);

    int work_minutes() const { return work_minutes_; }
    int short_break_minutes() const { return short_break_minutes_; }
    int long_break_minutes() const { return long_break_minutes_; }
    int long_break_interval() const { return long_break_interval_; }

private:
    int work_minutes_;
    int short_break_minutes_;
    int long_break_minutes_;
    int long_break_interval_;
};
