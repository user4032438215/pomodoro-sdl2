#include "app.hpp"
#include <SDL2/SDL.h>

App::App()
    : timer_(0),                    // ← 設定読み込み後に値を入れる
    session_(4, 25, 5, 15),       // ← 仮の初期値（init()で上書き）
    running_(true)
{
}

bool App::init()
{
    // ← 設定ファイル読み込み
    if (!settings_.load("settings.json")) {
        return false;
    }

    // ← 設定値で Session を初期化
    session_ = PomodoroSession(
        settings_.long_break_interval(),
        settings_.work_minutes(),
        settings_.short_break_minutes(),
        settings_.long_break_minutes()
    );

    // ← 設定値で Timer を初期化
    timer_.reset(settings_.work_minutes() * 60);

    return renderer_.init("Pomodoro", 640, 480);
}

void App::run()
{
    timer_.start();

    SDL_Event event;

    while (running_) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running_ = false;
            }
        }

        renderer_.clear();

        renderer_.render_session_name(session_.get_session_name());
        renderer_.render_timer(timer_.get_remaining_seconds(), timer_.get_progress());
        renderer_.render_progress_bar(timer_.get_progress());

        renderer_.present();

        if (timer_.is_finished()) {
            session_.next();
            timer_.reset(session_.get_duration_minutes() * 60);
            timer_.start();
        }

        SDL_Delay(16);
    }

    renderer_.shutdown();
}
