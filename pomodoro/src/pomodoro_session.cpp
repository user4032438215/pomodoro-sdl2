#include "pomodoro_session.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>

PomodoroSession::PomodoroSession(
    int long_break_interval,
    int work_minutes,
    int short_break_minutes,
    int long_break_minutes
)
    : completed_work_sessions_(0),
    long_break_interval_(std::max(1, long_break_interval)),
    work_minutes_(std::max(1, work_minutes)),
    short_break_minutes_(std::max(1, short_break_minutes)),
    long_break_minutes_(std::max(1, long_break_minutes)),
    current_(SessionType::WORK)
{
}

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

    assert(false && "Unknown SessionType");
    throw std::logic_error("Unknown SessionType");
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

    assert(false && "Unknown SessionType");
    throw std::logic_error("Unknown SessionType");
}

bool PomodoroSession::should_take_long_break() const
{
    return completed_work_sessions_ > 0
        && completed_work_sessions_ % long_break_interval_ == 0;
}

void PomodoroSession::next()
{
    if (current_ == SessionType::WORK) {
        ++completed_work_sessions_;

        current_ = should_take_long_break()
            ? SessionType::LONG_BREAK
            : SessionType::SHORT_BREAK;

        return;
    }

    current_ = SessionType::WORK;
}

void PomodoroSession::reset()
{
    completed_work_sessions_ = 0;
    current_ = SessionType::WORK;
}

SessionType PomodoroSession::get_type() const
{
    return current_;
}