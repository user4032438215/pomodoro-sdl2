#include "pomodoro_timer.hpp"

using SteadyClock = std::chrono::steady_clock;

PomodoroTimer::PomodoroTimer(int duration_sec)
    : duration_sec_(duration_sec),
    paused_elapsed_sec_(0),
    state_(TimerState::IDLE)
{
}

void PomodoroTimer::start()
{
    state_ = TimerState::RUNNING;
    paused_elapsed_sec_ = 0;
    started_at_ = SteadyClock::now();
}

void PomodoroTimer::pause()
{
    if (state_ == TimerState::RUNNING) {
        state_ = TimerState::PAUSED;
        paused_at_ = SteadyClock::now();
    }
}

void PomodoroTimer::resume()
{
    if (state_ == TimerState::PAUSED) {
        auto now = SteadyClock::now();
        auto paused_duration = std::chrono::duration_cast<std::chrono::seconds>(now - paused_at_);
        paused_elapsed_sec_ += static_cast<int>(paused_duration.count());
        state_ = TimerState::RUNNING;
    }
}

void PomodoroTimer::reset(int duration_sec)
{
    duration_sec_ = duration_sec;
    paused_elapsed_sec_ = 0;
    state_ = TimerState::IDLE;
}

int PomodoroTimer::get_remaining_seconds() const
{
    if (state_ == TimerState::IDLE) {
        return duration_sec_;
    }

    auto now = SteadyClock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - started_at_);
    int total_elapsed = static_cast<int>(elapsed.count()) - paused_elapsed_sec_;

    int remaining = duration_sec_ - total_elapsed;
    return remaining > 0 ? remaining : 0;
}

float PomodoroTimer::get_progress() const
{
    int remaining = get_remaining_seconds();
    return 1.0f - static_cast<float>(remaining) / static_cast<float>(duration_sec_);
}

bool PomodoroTimer::is_finished() const
{
    return get_remaining_seconds() <= 0;
}

TimerState PomodoroTimer::get_state() const
{
    return state_;
}
