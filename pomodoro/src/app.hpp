#pragma once
#include "pomodoro_timer.hpp"
#include "pomodoro_session.hpp"
#include "pomodoro_renderer.hpp"
#include "settings.hpp"

class App {
public:
    App();
    bool init();
    void run();

private:
    Settings settings_; 

    PomodoroTimer timer_;
    PomodoroSession session_;
    PomodoroRenderer renderer_;
    bool running_;

    void handle_events();   // 
};
