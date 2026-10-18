//pomodoro_timer.hpp
#pragma once
#include <chrono>

enum class TimerState {
    IDLE,
    RUNNING,
    PAUSED,
    FINISHED
};

class PomodoroTimer {
public:
    using Clock = std::chrono::steady_clock;
    using Duration = Clock::duration;
    using TimePoint = Clock::time_point;

    explicit PomodoroTimer(int duration_sec);

    void start();
    void pause();
    void resume();
    void reset(int duration_sec);
    void update();

    int get_remaining_seconds() const;
    float get_progress() const;
    bool is_finished() const;

    TimerState get_state() const;

private:
    int duration_sec_;

    Duration accumulated_elapsed_;   // 今まで動いた時間の合計
    TimePoint last_start_at_;        // 最後に動き始めた時刻
    TimerState state_;

    // ★ 新方式で必須（内部専用）
    Duration get_elapsed_duration() const;
};
