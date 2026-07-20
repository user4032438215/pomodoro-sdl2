#include "pomodoro_timer.hpp"

PomodoroTimer::PomodoroTimer(int duration_sec)
    : duration_sec_(duration_sec),
    remaining_sec_(duration_sec),
    running_(false) {
}

void PomodoroTimer::start() {
    running_ = true;
    start_time_ = std::chrono::steady_clock::now();
}

void PomodoroTimer::reset(int duration_sec) {
    duration_sec_ = duration_sec;
    remaining_sec_ = duration_sec;
    running_ = false;
}

void PomodoroTimer::update() {
    if (!running_) return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time_).count();

    remaining_sec_ = duration_sec_ - static_cast<int>(elapsed);
    if (remaining_sec_ < 0) remaining_sec_ = 0;
}

int PomodoroTimer::get_remaining_seconds() const {
    return remaining_sec_;
}

float PomodoroTimer::get_progress() const {
    return 1.0f - (static_cast<float>(remaining_sec_) / duration_sec_);
}

bool PomodoroTimer::is_finished() const {
    return remaining_sec_ <= 0;
}
