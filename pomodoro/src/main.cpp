#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "pomodoro_renderer.hpp"

int main()
{
    PomodoroRenderer renderer;

    if (!renderer.init("Pomodoro MVP", 640, 480)) {
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.clear();
        renderer.render_text("Pomodoro MVP Renderer Test", 50, 50);
        renderer.present();

        SDL_Delay(16); // 約60FPS
    }

    renderer.shutdown();
    return 0;
}
