#include "app.hpp"
#include <SDL2/SDL.h>

App::App()
    : timer_(25 * 60),
    session_(4),
    running_(true)
{
}

bool App::init()
{
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

        renderer_.render_progress_bar(timer_.get_progress()); //


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
