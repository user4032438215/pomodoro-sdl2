#pragma once
#include <string>

enum class SessionType {
    WORK,
    SHORT_BREAK,
    LONG_BREAK
};

class PomodoroSession {
public:
    PomodoroSession(
        int long_break_interval,
        int work_minutes,
        int short_break_minutes,
        int long_break_minutes
    );

    void next();
    void reset();

    SessionType get_type() const;
    int get_duration_minutes() const;
    std::string get_session_name() const;

    bool should_take_long_break() const;

private:
    int completed_work_sessions_;
    int long_break_interval_;
    

    // ★追加
    int work_minutes_;            
    int short_break_minutes_;     
    int long_break_minutes_;      

    SessionType current_;

};
