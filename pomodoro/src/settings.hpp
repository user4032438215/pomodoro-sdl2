//settings.hpp
// インライン関数使用
#pragma once

#include <string>

struct PomodoroConfig
{
    int work_minutes{ 25 };
    int short_break_minutes{ 5 };
    int long_break_minutes{ 15 };
    int long_break_interval{ 4 };
};

class Settings {
public:
    Settings() = default;

    bool load(const std::string& path);

    //bool save(const std::string& path) const; 将来的に実装

    bool validate() const noexcept;

    
    //const PomodoroConfig& current() const;
    const PomodoroConfig& current() const noexcept
    {
        return config_;
    }

    // ☆ デフォルト値は、毎回新しい値として渡す
    PomodoroConfig defaults() const noexcept
    {
        return PomodoroConfig{};
    }

private:
    PomodoroConfig config_{};

};