#include "pomodoro_renderer.hpp"
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
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        return false;
    }

    //font_ = TTF_OpenFont("NotoSans-Regular.ttf", 32);
    font_ = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
    if (!font_) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << "\n";
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
