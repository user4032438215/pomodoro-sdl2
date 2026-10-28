// button.hpp
#pragma once

#include <string>
#include <SDL2/SDL.h>

class PomodoroRenderer;

class Button
{
public:
    Button(
        SDL_Rect rect,
        std::string label
    );

    bool contains_point(
        int x,
        int y
    ) const;

    void render(
        PomodoroRenderer& renderer
    ) const;

    const std::string& label() const;

    void set_label(const std::string& label);

private:
    SDL_Rect rect_{};
    std::string label_;
};