#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class PomodoroRenderer {
public:
    PomodoroRenderer();
    ~PomodoroRenderer();

    bool init(const std::string& title, int width, int height);
    void shutdown();

    void clear();
    void render_text(const std::string& text, int x, int y);
    void present();

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    TTF_Font* font_;
};
