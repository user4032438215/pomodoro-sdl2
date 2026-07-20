#pragma once
#include <string>

enum class SessionType {
    Work,
    ShortBreak,
    LongBreak
};

class PomodoroSession {
public:
    explicit PomodoroSession(int long_break_interval);

    void next();
    SessionType get_type() const;
    int get_duration_minutes() const;
    std::string get_session_name() const;

private:
    int work_count_;
    int long_break_interval_;
    SessionType current_;
};
