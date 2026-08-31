#include "pomodoro_session.hpp"

PomodoroSession::PomodoroSession(int long_break_interval)
    : completed_work_sessions_(0),
    long_break_interval_(long_break_interval),
    current_(SessionType::WORK)
{
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

int PomodoroSession::get_duration_minutes() const
{
    switch (current_) {
    case SessionType::WORK:
        return 25;
    case SessionType::SHORT_BREAK:
        return 5;
    case SessionType::LONG_BREAK:
        return 15;
    }
    return 25;
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
