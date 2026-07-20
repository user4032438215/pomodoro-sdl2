//#include <SDL.h>
//#include <SDL_ttf.h>
#include <iostream>
//#include <chrono>


#include <thread>
#include "pomodoro_timer.hpp"
#include "pomodoro_session.hpp"

int main() {
    PomodoroSession session(3);
    PomodoroTimer timer(session.get_duration_minutes() * 60);

    timer.start();

    while (true) {
        timer.update();

        std::cout << "Session: " << session.get_session_name()
            << " | Remaining: " << timer.get_remaining_seconds()
            << " sec"
            << " | Progress: " << timer.get_progress()
            << std::endl;

        if (timer.is_finished()) {
            std::cout << "Session finished! Switching..." << std::endl;

            session.next();
            timer.reset(session.get_duration_minutes() * 60);
            timer.start();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}
