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
    void handle_events();
    void update();
    void render();
    void start_current_session();

    // ☆ settings_を最初に宣言する
    // PomodoroSessionがSettingsを参照するため
    Settings settings_;

    // ☆ Settingsを参照する構成
    PomodoroSession session_;

    PomodoroTimer timer_;
    PomodoroRenderer renderer_;

    bool running_{ true };
};