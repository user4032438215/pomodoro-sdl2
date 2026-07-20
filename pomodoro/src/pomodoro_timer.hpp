#pragma once
#include <chrono>

class PomodoroTimer {
public:
    explicit PomodoroTimer(int duration_sec);

    void start();
    void reset(int duration_sec);
    void update();

    int get_remaining_seconds() const;
    float get_progress() const;
    bool is_finished() const;

private:
    int duration_sec_;
    int remaining_sec_;
    bool running_;

    std::chrono::steady_clock::time_point start_time_;
};
