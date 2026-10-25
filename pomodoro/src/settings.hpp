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

    bool validate() const noexcept;

    //added 261025
    bool apply(const PomodoroConfig& draft);
    bool save(const std::string& path) const;

    
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

    //added for apply
    bool validate_config(
        const PomodoroConfig& config
    ) const noexcept;

    PomodoroConfig config_{};

};