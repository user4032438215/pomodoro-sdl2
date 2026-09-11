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
    explicit PomodoroTimer(int duration_sec);

    void start();
    void pause();
    void resume();
    void reset(int duration_sec);

    int get_remaining_seconds() const;
    float get_progress() const;
    bool is_finished() const;

    TimerState get_state() const;

private:
    int duration_sec_;
    int paused_elapsed_sec_;

    TimerState state_;

    std::chrono::steady_clock::time_point started_at_;
    std::chrono::steady_clock::time_point paused_at_;
};
