#pragma once
#include <string>

enum class SessionType {
    WORK,
    SHORT_BREAK,
    LONG_BREAK
};

class PomodoroSession {
public:
    explicit PomodoroSession(int long_break_interval);

    void next();
    void reset();

    SessionType get_type() const;
    int get_duration_minutes() const;
    std::string get_session_name() const;

    bool should_take_long_break() const;

private:
    int completed_work_sessions_;
    int long_break_interval_;
    SessionType current_;
};
