#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
    // SDL 初期化
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // SDL_ttf 初期化
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Pomodoro Timer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // フォント読み込み（好きなフォントに変えてOK）
    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 64);
    if (!font) {
        std::cerr << "Font load error: " << TTF_GetError() << std::endl;
        return 1;
    }

    // chrono タイマー準備
    using clock = std::chrono::steady_clock;
    const int totalSeconds = 25 * 60;
    auto startTime = clock::now();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // 経過時間
        auto now = clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        int remaining = totalSeconds - elapsed;
        if (remaining < 0) remaining = 0;

        int minutes = remaining / 60;
        int seconds = remaining % 60;

        // MM:SS の文字列を作る
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);

        // SDL_ttf でテキスト描画準備
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Blended(font, buffer, white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // テキストのサイズ
        int textW = surface->w;
        int textH = surface->h;
        SDL_FreeSurface(surface);

        SDL_Rect dst = {
            320 - textW / 2,
            240 - textH / 2,
            textW,
            textH
        };

        // 背景クリア
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // テキスト描画
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
