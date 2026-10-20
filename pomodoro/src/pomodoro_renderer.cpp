// pomodoro_renderer.cpp
#include "pomodoro_renderer.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>

PomodoroRenderer::PomodoroRenderer()
    : window_(nullptr),
    renderer_(nullptr),
    font_(nullptr)
{
}

PomodoroRenderer::~PomodoroRenderer()
{
    shutdown();
}

bool PomodoroRenderer::init(const std::string& title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << "\n";
        return false;
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window_) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        shutdown();
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        shutdown();
        return false;
    }

    //font_ = TTF_OpenFont("NotoSans-Regular.ttf", 32);
    font_ = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
    if (!font_) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << "\n";
        shutdown();
        return false;
    }

    return true;
}

void PomodoroRenderer::shutdown()
{
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }

    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}

void PomodoroRenderer::clear()
{
    SDL_SetRenderDrawColor(renderer_, 30, 30, 30, 255);
    SDL_RenderClear(renderer_);
}

void PomodoroRenderer::render_text(const std::string& text, int x, int y)
{
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font_, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);

    if (!texture) return;

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);

    SDL_RenderCopy(renderer_, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

void PomodoroRenderer::present()
{
    SDL_RenderPresent(renderer_);
}

void PomodoroRenderer::render_timer(int remaining_sec, float progress)
{
    {
        render_text(
            format_time(remaining_sec),
            220,
            180
        );

        const int percent =
            static_cast<int>(progress * 100.0f);

        render_text(
            "Progress: " +
            std::to_string(percent) +
            "%",
            220,
            230
        );
    }
}

void PomodoroRenderer::render_session_name(const std::string& name)
{
    render_text("Session: " + name, 50, 70);
}

void PomodoroRenderer::render_progress_bar(float progress) //
{
    const int x = 50;
    const int y = 400;
    const int width = 500;
    const int height = 20;

    // 背景バー（灰色）
    SDL_Rect bg;
    bg.x = x;
    bg.y = y;
    bg.w = width;
    bg.h = height;

    SDL_SetRenderDrawColor(renderer_, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer_, &bg);

    // 進捗バー（緑）
    SDL_Rect fg;
    fg.x = x;
    fg.y = y;
    fg.w = static_cast<int>(width * progress);
    fg.h = height;

    SDL_SetRenderDrawColor(renderer_, 0, 200, 0, 255);
    SDL_RenderFillRect(renderer_, &fg);
}

void PomodoroRenderer::render_button(
    const SDL_Rect& bounds,
    const std::string& label
)
{
    // ☆ ボタンの背景
    SDL_SetRenderDrawColor(
        renderer_,
        31, 31, 31, 255
    );

    SDL_RenderFillRect(
        renderer_,
        &bounds
    );

    // ☆ ボタンの枠
    SDL_SetRenderDrawColor(
        renderer_,
        80, 80, 80, 255
    );

    SDL_RenderDrawRect(
        renderer_,
        &bounds
    );

    // ☆ 文字
    render_text(
        label,
        bounds.x + 20,
        bounds.y + 10
    );
}


//added SSSS to MM:SS
std::string PomodoroRenderer::format_time(
    int remaining_sec
) const
{
    // ☆ 念のため負数を0として扱う
    const int safe_seconds =
        std::max(0, remaining_sec);

    const int minutes =
        safe_seconds / 60;

    const int seconds =
        safe_seconds % 60;

    char buffer[16]{};

    std::snprintf(
        buffer,
        sizeof(buffer),
        "%02d:%02d",
        minutes,
        seconds
    );

    return std::string(buffer);
}