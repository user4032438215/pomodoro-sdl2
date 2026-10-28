// button.cpp
#include "button.hpp"

#include "pomodoro_renderer.hpp"

Button::Button(
    SDL_Rect rect,
    std::string label
)
    : rect_(rect),
    label_(std::move(label))
{
}

bool Button::contains_point(
    int x,
    int y
) const
{
    return
        x >= rect_.x &&
        x < rect_.x + rect_.w &&
        y >= rect_.y &&
        y < rect_.y + rect_.h;
}

void Button::render(
    PomodoroRenderer& renderer
) const
{
    renderer.render_button(
        rect_,
        label_
    );
}

const std::string& Button::label() const
{
    return label_;
}

void Button::set_label(
    const std::string& label
)
{
    label_ = label;
}