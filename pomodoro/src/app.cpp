//app.cpp
#include "app.hpp"
#include <iostream>
#include <SDL2/SDL.h>

//added for std::min/max
#include <algorithm>

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

//updated handle_events()
void App::handle_events()
{
    SDL_Event event{};

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running_ = false;
            continue;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN &&
            event.button.button == SDL_BUTTON_LEFT)
        {
            const int x = event.button.x;
            const int y = event.button.y;

            // Timer screen
            if (screen_ == AppScreen::TIMER) {
                if (is_inside(start_button_, x, y)) {
                    if (timer_.get_state() == TimerState::IDLE) {
                        timer_.start();
                    }
                    else if (timer_.get_state() == TimerState::RUNNING) {
                        timer_.pause();
                    }
                    else if (timer_.get_state() == TimerState::PAUSED) {
                        timer_.resume();
                    }
                }

                if (is_inside(reset_button_, x, y)) {
                    reset_current_timer();
                }

                if (is_inside(settings_button_, x, y)) {
                    settings_draft_ = settings_.current();
                    screen_ = AppScreen::SETTINGS;
                }
            }

            // Settings screen
            else if (screen_ == AppScreen::SETTINGS) {

                
                if (is_inside(work_minus_button_, x, y)) {
                    std::cout << "work_minus_button clicked\n";

                    settings_draft_.work_minutes =
                        std::max(
                            5,
                            settings_draft_.work_minutes - 5
                        );
                }

                //work
                if (is_inside(work_plus_button_, x, y)) {
                    std::cout << "work_plus_button clicked\n";

                    settings_draft_.work_minutes =
                        std::min(
                            60,
                            settings_draft_.work_minutes + 5
                        );
                }

                //short_break
                if (is_inside(short_break_minus_button_, x, y)) {
                    std::cout << "short_break_minus_button clicked\n";

                    settings_draft_.short_break_minutes =
                        std::max(
                            5,
                            settings_draft_.short_break_minutes - 5
                        );
                }

                if (is_inside(short_break_plus_button_, x, y)) {
                    std::cout << "short_break_plus_button clicked\n";

                    settings_draft_.short_break_minutes =
                        std::min(
                            60,
                            settings_draft_.short_break_minutes + 5
                        );
                }

                //long_break
                if (is_inside(long_break_minus_button_, x, y)) {
                    std::cout << "long_break_minus_button clicked\n";

                    settings_draft_.long_break_minutes =
                        std::max(
                            5,
                            settings_draft_.long_break_minutes - 5
                        );
                }

                if (is_inside(long_break_plus_button_, x, y)) {
                    std::cout << "long_break_plus_button clicked\n";

                    settings_draft_.long_break_minutes =
                        std::min(
                            60,
                            settings_draft_.long_break_minutes + 5
                        );
                }


                if (is_inside(back_button_, x, y)) {
                    screen_ = AppScreen::TIMER;
                }
            }

            continue;
        }

        if (event.type != SDL_KEYDOWN) {
            continue;
        }

        if (event.key.repeat != 0) {
            continue;
        }

        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            running_ = false;
            break;

        case SDLK_SPACE:
            if (screen_ == AppScreen::TIMER) {
                if (timer_.get_state() == TimerState::IDLE) {
                    timer_.start();
                }
                else if (timer_.get_state() == TimerState::RUNNING) {
                    timer_.pause();
                }
                else if (timer_.get_state() == TimerState::PAUSED) {
                    timer_.resume();
                }
            }
            break;

        case SDLK_r:
            if (screen_ == AppScreen::TIMER) {
                reset_current_timer();
            }
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

    if (screen_ == AppScreen::TIMER) {
        render_timer_screen();
    }
    else if (screen_ == AppScreen::SETTINGS) {
        render_settings_screen();
    }

    renderer_.present();
}

void App::render_timer_screen()
{
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

    renderer_.render_button(
        reset_button_,
        "RESET"
    );

    renderer_.render_button(
        start_button_,
        button_label()
    );

    renderer_.render_button(
        settings_button_,
        "SETTINGS"
    );
}

void App::render_settings_screen()
{
    //added
    const PomodoroConfig& current =
        settings_.current();

    renderer_.render_text(
        "Settings",
        270,
        80
    );
    
    renderer_.render_text(
        "Work: " +
        std::to_string(settings_draft_.work_minutes) +
        " min",
        220,
        160
    );

    renderer_.render_text(
        "Short Break: " +
        std::to_string(settings_draft_.short_break_minutes) +
        " min",
        220,
        200
    );

    renderer_.render_text(
        "Long Break: " +
        std::to_string(settings_draft_.long_break_minutes) +
        " min",
        220,
        240
    );

    renderer_.render_text(
        "Long Break Interval: " +
        std::to_string(settings_draft_.long_break_interval),
        220,
        280
    );

    //work
    renderer_.render_button(
        work_minus_button_,
        "-"
    );

    renderer_.render_button(
        work_plus_button_,
        "+"
    );

    //short_break
    renderer_.render_button(
        short_break_minus_button_,
        "-"
    );

    renderer_.render_button(
        short_break_plus_button_,
        "+"
    );

    //long_break
    renderer_.render_button(
        long_break_minus_button_,
        "-"
    );

    renderer_.render_button(
        long_break_plus_button_,
        "+"
    );

    //long_break_int

    //back
    renderer_.render_button(
        back_button_,
        "BACK"
    );
}

/*
added
マウスのxが、ボタンの左端以上
かつ
マウスのxが、ボタンの右端より小さい
かつ
マウスのyが、ボタンの上端以上
かつ
マウスのyが、ボタンの下端より小さい
*/
bool App::is_inside(
    const SDL_Rect& rect,
    int x,
    int y
) const
{
    return
        x >= rect.x &&
        x < rect.x + rect.w &&
        y >= rect.y &&
        y < rect.y + rect.h;
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

std::string App::button_label() const
{
    switch (timer_.get_state()) {
    case TimerState::IDLE:
        return "START";

    case TimerState::RUNNING:
        return "PAUSE";

    case TimerState::PAUSED:
        return "RESUME";

    default:
        return "START";
    }
}