#include <iostream>
#include <thread>
#include "pomodoro_timer.hpp"

int main() {
    PomodoroTimer timer(5); // 5秒のテストタイマー

    std::cout << "start()" << std::endl;
    timer.start();

    // 2秒待つ
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "残り: " << timer.get_remaining_seconds() << " 秒" << std::endl;

    std::cout << "pause()" << std::endl;
    timer.pause();

    // 2秒待つ（pause中なので減らない）
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "pause中の残り: " << timer.get_remaining_seconds() << " 秒" << std::endl;

    std::cout << "resume()" << std::endl;
    timer.resume();

    // 2秒待つ（resumeしたので減る）
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "再開後の残り: " << timer.get_remaining_seconds() << " 秒" << std::endl;

    std::cout << "is_finished(): " << timer.is_finished() << std::endl;

    return 0;
}
