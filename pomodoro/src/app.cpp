#include "app.hpp"
#include <iostream>
#include <SDL2/SDL.h>

App::App()
    : settings_(),
    session_(settings_),
    timer_(1),
    renderer_(),
    running_(true)
{
}

bool App::init()
{
    std::cout << "[App] Loading settings...\n";

    if (!settings_.load("settings.json")) {
        std::cerr << "[App] Failed to load settings.json\n";
        return false;
    }

    std::cout << "[App] Settings loaded\n";

    if (!settings_.validate()) {
        std::cerr << "[App] Settings validation failed\n";
        return false;
    }

    std::cout << "[App] Settings validated\n";

    //start_current_session();
    reset_current_timer();

    std::cout << "[App] Initializing renderer...\n";

    if (!renderer_.init("Pomodoro", 640, 480)) {
        std::cerr << "[App] Renderer initialization failed\n";
        return false;
    }

    std::cout << "[App] Initialization completed\n";
    return true;
}

void App::run()
{
    
    //timer_.start();

    while (running_) {
        handle_events();

        // ☆ RUNNING中の時間切れをFINISHEDへ反映する
        timer_.update();

        // ☆ 終了していれば次のセッションへ進める
        update();

        // ☆ 現在の状態を描画する
        render();

        // 約60FPS
        SDL_Delay(16);
    }

    renderer_.shutdown();
}

void App::handle_events()
{
    SDL_Event event{};

    // SDL_PollEventは保留中のイベントを1つずつ取り出します。
    // すべてのイベントを処理するためwhileで呼び出します。[127]
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running_ = false;
            continue;
        }

        if (event.type != SDL_KEYDOWN) {
            continue;
        }

        // キーリピートによる連続処理を避ける
        if (event.key.repeat != 0) {
            continue;
        }

        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            running_ = false;
            break;

        //case SDLK_SPACE:
        //    if (timer_.get_state() == TimerState::RUNNING) {
        //        timer_.pause();
        //    }
        //    else if (timer_.get_state() == TimerState::PAUSED) {
        //        timer_.resume();
        //    }
        //    break;

        case SDLK_SPACE:
            if (timer_.get_state() == TimerState::IDLE) {
                timer_.start();
            }
            else if (timer_.get_state() == TimerState::RUNNING) {
                timer_.pause();
            }
            else if (timer_.get_state() == TimerState::PAUSED) {
                timer_.resume();
            }
            break;

        case SDLK_r:
            // ☆ 現在のセッションを最初からやり直す
            timer_.reset(
                session_.get_duration_minutes() * 60
            );
            timer_.start();
            break;

        case SDLK_n:
            // ☆ 現在のセッションを途中で終了して次へ進む
            session_.next();
            start_current_session();
            break;

        default:
            break;
        }
    }
}

void App::update()
{
    if (!timer_.is_finished()) {
        return;
    }

    // ☆ WORK終了、休憩終了などの状態遷移はSessionに任せる
    session_.next();

    // ☆ 次のセッションを設定するだけ
    reset_current_timer();
}

void App::render()
{
    renderer_.clear();

    renderer_.render_session_name(
        session_.get_session_name()
    );

    renderer_.render_timer(
        timer_.get_remaining_seconds(),
        timer_.get_progress()
    );

    renderer_.render_progress_bar(
        timer_.get_progress()
    );

    renderer_.present();
}

void App::start_current_session()
{
    const int duration_seconds =
        session_.get_duration_minutes() * 60;

    timer_.reset(duration_seconds);
    timer_.start();
}

void App::reset_current_timer()
{
    const int duration_seconds =
        session_.get_duration_minutes() * 60;

    timer_.reset(duration_seconds);

    // ☆ start()を呼ばない
}

void App::start_current_timer()
{
    if (timer_.get_state() == TimerState::IDLE) {
        timer_.start();
    }
}

//added for tests
TimerState App::timer_state() const noexcept
{
    return timer_.get_state();
}

SessionType App::session_type() const noexcept
{
    return session_.get_type();
}

int App::remaining_seconds() const
{
    return timer_.get_remaining_seconds();
}

float App::progress() const
{
    return timer_.get_progress();
}