#include "app.hpp"

int main()
{
    App app;

    if (!app.init()) {
        return 1;
    }

    app.run();
    return 0;
}
// 
// 
//#include <iostream>
//#include <thread>
//#include "pomodoro_timer.hpp"
//#include "pomodoro_session.hpp"
//#include "settings.hpp"
//
//int main()
//{
//    Settings settings;
//    settings.load("settings.json");
//
//    PomodoroSession session(
//        settings.long_break_interval(),
//        settings.work_minutes(),
//        settings.short_break_minutes(),
//        settings.long_break_minutes()
//    );
//
//    PomodoroTimer timer(session.get_duration_minutes() * 60);
//
//    std::cout << "=== Pomodoro Core Test ===\n";
//
//    timer.start();
//    std::cout << "Start: remaining=" << timer.get_remaining_seconds() << "\n";
//
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    std::cout << "After 3 sec: remaining=" << timer.get_remaining_seconds() << "\n";
//
//    timer.pause();
//    std::cout << "Paused: remaining=" << timer.get_remaining_seconds() << "\n";
//
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    std::cout << "While paused (3 sec): remaining=" << timer.get_remaining_seconds() << "\n";
//
//    timer.resume();
//    std::cout << "Resumed: remaining=" << timer.get_remaining_seconds() << "\n";
//
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    std::cout << "After resume (3 sec): remaining=" << timer.get_remaining_seconds() << "\n";
//
//    return 0;
//}
