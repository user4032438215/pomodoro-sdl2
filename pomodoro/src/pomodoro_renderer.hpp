// pomodoro_renderer.hpp
#pragma once

#include "pomodoro_timer.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class PomodoroRenderer {
public:
    PomodoroRenderer();
    ~PomodoroRenderer();

    bool init(
        const std::string& title,
        int width,
        int height
    );

    void shutdown();

    void clear();
    //void render_text(const std::string& text, int x, int y);
    void present();



    void render_timer(
        int remaining_sec, 
        float progress
    );

    void render_session_name(
        const std::string& name
    );

    void render_progress_bar(
        float progress
    ); 

    //added
    void render_button(
        const SDL_Rect& bounds,
        const std::string& label
    );

    void render_text(
        const std::string& text,
        int x,
        int y
    );

    //void render_state(TimerState state);


private:

    // ☆ 表示専用の変換
    std::string format_time(
        int remaining_sec
    ) const;



    SDL_Window* window_;
    SDL_Renderer* renderer_;
    TTF_Font* font_;
};
