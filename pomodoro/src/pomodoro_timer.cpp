#include "pomodoro_timer.hpp"

#include <algorithm>
#include <chrono>

PomodoroTimer::PomodoroTimer(int duration_sec)
    : duration_sec_(std::max(1, duration_sec)),
    accumulated_elapsed_(Duration::zero()),
    last_start_at_{},
    state_(TimerState::IDLE)
{
}

void PomodoroTimer::start()
{
    if (state_ != TimerState::IDLE) {
        return;
    }

    accumulated_elapsed_ = Duration::zero();
    last_start_at_ = Clock::now();
    state_ = TimerState::RUNNING;
}

void PomodoroTimer::pause()
{
    if (state_ != TimerState::RUNNING) {
        return;
    }

    const auto now = Clock::now();
    accumulated_elapsed_ += now - last_start_at_;
    state_ = TimerState::PAUSED;
}

void PomodoroTimer::resume()
{
    if (state_ != TimerState::PAUSED) {
        return;
    }

    last_start_at_ = Clock::now();
    state_ = TimerState::RUNNING;
}

void PomodoroTimer::reset(int duration_sec)
{
    duration_sec_ = std::max(1, duration_sec);
    accumulated_elapsed_ = Duration::zero();
    last_start_at_ = TimePoint{};
    state_ = TimerState::IDLE;
}

void PomodoroTimer::update()
{
    if (state_ != TimerState::RUNNING) {
        return;
    }

    if (get_elapsed_duration() >= std::chrono::seconds(duration_sec_)) {
        const auto now = Clock::now();
        accumulated_elapsed_ += now - last_start_at_;
        state_ = TimerState::FINISHED;
    }
}

PomodoroTimer::Duration PomodoroTimer::get_elapsed_duration() const
{
    if (state_ == TimerState::RUNNING) {
        return accumulated_elapsed_ + (Clock::now() - last_start_at_);
    }

    return accumulated_elapsed_;
}

int PomodoroTimer::get_remaining_seconds() const // 切り上げ処理に変更
{
    const auto elapsed = get_elapsed_duration();
    const auto total = std::chrono::seconds(duration_sec_);

    if (elapsed >= total) {
        return 0;
    }

    const auto remaining =
        std::chrono::ceil<std::chrono::seconds>(
            total - elapsed
        );

    return static_cast<int>(remaining.count());
}

float PomodoroTimer::get_progress() const
{
    //if (duration_sec_ <= 0) {
    //    return 1.0f;
    //}

    const double elapsed_sec =
        std::chrono::duration<double>(
            get_elapsed_duration()
        ).count();

    const double progress = elapsed_sec / duration_sec_;

    return static_cast<float>(
        std::clamp(progress, 0.0, 1.0)
        );
}

bool PomodoroTimer::is_finished() const
{
    return state_ == TimerState::FINISHED;
}

TimerState PomodoroTimer::get_state() const
{
    return state_;
}