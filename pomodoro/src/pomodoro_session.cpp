#include "pomodoro_session.hpp"

PomodoroSession::PomodoroSession(int long_break_interval)
    : work_count_(0),
    long_break_interval_(long_break_interval),
    current_(SessionType::Work) {
}

void PomodoroSession::next() {
    if (current_ == SessionType::Work) {
        work_count_++;

        if (work_count_ % long_break_interval_ == 0) {
            current_ = SessionType::LongBreak;
        }
        else {
            current_ = SessionType::ShortBreak;
        }
    }
    else {
        current_ = SessionType::Work;
    }
}

SessionType PomodoroSession::get_type() const {
    return current_;
}

int PomodoroSession::get_duration_minutes() const {
    switch (current_) {
    case SessionType::Work:       return 25;
    case SessionType::ShortBreak: return 5;
    case SessionType::LongBreak:  return 15;
    }
    return 25;
}

std::string PomodoroSession::get_session_name() const {
    switch (current_) {
    case SessionType::Work:       return "Work";
    case SessionType::ShortBreak: return "Short Break";
    case SessionType::LongBreak:  return "Long Break";
    }
    return "Work";
}
