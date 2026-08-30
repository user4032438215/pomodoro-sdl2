#include "pomodoro_timer.hpp"

using clock_type = std::chrono::steady_clock;

// コンストラクタ
PomodoroTimer::PomodoroTimer(int duration_sec)
    : duration_sec_(duration_sec),
    paused_elapsed_sec_(0),
    state_(TimerState::Idle)
{
}

// タイマー開始
void PomodoroTimer::start()
{
    state_ = TimerState::Running;
    paused_elapsed_sec_ = 0;
    started_at_ = clock_type::now();
}

// 一時停止
void PomodoroTimer::pause()
{
    if (state_ == TimerState::Running) {
        state_ = TimerState::Paused;
        paused_at_ = clock_type::now();
    }
}

// 再開
void PomodoroTimer::resume()
{
    if (state_ == TimerState::Paused) {
        auto now = clock_type::now();
        auto paused_duration = std::chrono::duration_cast<std::chrono::seconds>(now - paused_at_);
        paused_elapsed_sec_ += paused_duration.count();

        state_ = TimerState::Running;
    }
}

// リセット
void PomodoroTimer::reset(int duration_sec)
{
    duration_sec_ = duration_sec;
    paused_elapsed_sec_ = 0;
    state_ = TimerState::Idle;
}

// 残り秒数
int PomodoroTimer::get_remaining_seconds() const
{
    if (state_ == TimerState::Idle) {
        return duration_sec_;
    }

    auto now = clock_type::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - started_at_);
    int total_elapsed = static_cast<int>(elapsed.count()) - paused_elapsed_sec_;

    int remaining = duration_sec_ - total_elapsed;
    return remaining > 0 ? remaining : 0;
}

// 進捗（0.0〜1.0）
float PomodoroTimer::get_progress() const
{
    int remaining = get_remaining_seconds();
    return 1.0f - static_cast<float>(remaining) / static_cast<float>(duration_sec_);
}

// 終了判定
bool PomodoroTimer::is_finished() const
{
    return get_remaining_seconds() <= 0;
}

// 状態取得
TimerState PomodoroTimer::get_state() const
{
    return state_;
}
