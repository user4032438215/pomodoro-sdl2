#include "pomodoro_session.hpp"


// ★変更：設定値を受け取る新コンストラクタ
PomodoroSession::PomodoroSession(int long_break_interval,
    int work_minutes,
    int short_break_minutes,
    int long_break_minutes)
    : completed_work_sessions_(0),
    long_break_interval_(long_break_interval),
    work_minutes_(work_minutes),            // ★追加済みメンバ
    short_break_minutes_(short_break_minutes),
    long_break_minutes_(long_break_minutes),
    current_(SessionType::WORK)
{
}

// ★変更：設定値を返す get_duration_minutes（これが正しい）
int PomodoroSession::get_duration_minutes() const
{
    switch (current_) {
    case SessionType::WORK:
        return work_minutes_;
    case SessionType::SHORT_BREAK:
        return short_break_minutes_;
    case SessionType::LONG_BREAK:
        return long_break_minutes_;
    }
    return work_minutes_;
}

void PomodoroSession::reset()
{
    completed_work_sessions_ = 0;
    current_ = SessionType::WORK;
}

bool PomodoroSession::should_take_long_break() const
{
    return (completed_work_sessions_ > 0 &&
        completed_work_sessions_ % long_break_interval_ == 0);
}

void PomodoroSession::next()
{
    if (current_ == SessionType::WORK) {
        completed_work_sessions_++;

        if (should_take_long_break()) {
            current_ = SessionType::LONG_BREAK;
        }
        else {
            current_ = SessionType::SHORT_BREAK;
        }
    }
    else {
        current_ = SessionType::WORK;
    }
}

SessionType PomodoroSession::get_type() const
{
    return current_;
}



std::string PomodoroSession::get_session_name() const
{
    switch (current_) {
    case SessionType::WORK:
        return "Work";
    case SessionType::SHORT_BREAK:
        return "Short Break";
    case SessionType::LONG_BREAK:
        return "Long Break";
    }
    return "Work";
}
