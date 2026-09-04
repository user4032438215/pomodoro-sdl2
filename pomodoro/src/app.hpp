#pragma once
#include "pomodoro_timer.hpp"
#include "pomodoro_session.hpp"
#include "pomodoro_renderer.hpp"

class App {
public:
    App();
    bool init();
    void run();

private:
    PomodoroTimer timer_;
    PomodoroSession session_;
    PomodoroRenderer renderer_;
    bool running_;
};
