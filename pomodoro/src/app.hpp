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

    //added for tests
    TimerState timer_state() const noexcept;
    SessionType session_type() const noexcept;
    int remaining_seconds() const;
    float progress() const;

private:
    void handle_events();
    void update();
    void render();
    void start_current_session();
    void reset_current_timer();
    void start_current_timer();

    // ☆ settings_を最初に宣言する
    // PomodoroSessionがSettingsを参照するため
    Settings settings_;

    // ☆ Settingsを参照する構成
    PomodoroSession session_;

    PomodoroTimer timer_;
    PomodoroRenderer renderer_;

    bool running_{ true };
};