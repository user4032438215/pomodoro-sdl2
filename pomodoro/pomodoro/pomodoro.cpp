#include <SDL.h>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
    // SDL の初期化
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // ウィンドウ作成
    SDL_Window* window = SDL_CreateWindow(
        "Pomodoro Timer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // -----------------------------
    // ここから chrono タイマーの準備
    // -----------------------------
    using clock = std::chrono::steady_clock;

    const int totalSeconds = 25 * 60; // 25分
    auto startTime = clock::now();    // タイマー開始時刻

    bool running = true;
    SDL_Event event;

    while (running) {
        // イベント処理（×ボタンなど）
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // -----------------------------
        // chrono で経過時間を計算
        // -----------------------------
        auto now = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        int remaining = totalSeconds - elapsed;

        if (remaining < 0) remaining = 0;

        // MM:SS に整形
        int minutes = remaining / 60;
        int seconds = remaining % 60;

        // コンソールに出力（UIなし）
        std::cout << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << "\r";
        std::cout.flush();

        // SDL のループを軽く休ませる（CPU暴走防止）
        SDL_Delay(16); // 約60fps
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
