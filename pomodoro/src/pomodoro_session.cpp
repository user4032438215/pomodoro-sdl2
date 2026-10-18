//pomodoro_session.cpp
#include "pomodoro_session.hpp"

//#include <algorithm>
//#include <cassert>
#include <stdexcept>

PomodoroSession::PomodoroSession(const Settings& settings)
    : settings_(settings)
{
}


int PomodoroSession::get_duration_minutes() const
{
    const PomodoroConfig& config =
    settings_.current();

    switch (current_) {
    case SessionType::WORK:
        return config.work_minutes;

    case SessionType::SHORT_BREAK:
        return config.short_break_minutes;

    case SessionType::LONG_BREAK:
        return config.long_break_minutes;

    default:
        throw std::logic_error("Unknown SessionType");
    }
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

    default:
        throw std::logic_error("Unknown SessionType"); //不正値
    }
}

bool PomodoroSession::should_take_long_break() const
{
    return completed_work_sessions_ > 0 &&
           completed_work_sessions_ % settings_.current().long_break_interval == 0;
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

SessionType PomodoroSession::get_type() const noexcept
{
    return current_;
}


int PomodoroSession::completed_work_sessions() const noexcept
{
    return completed_work_sessions_;
}