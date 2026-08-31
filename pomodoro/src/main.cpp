#include <iostream>
#include <thread>

#include "pomodoro_timer.hpp"
#include "pomodoro_session.hpp"

int main()
{
    PomodoroSession session(4); // 4回作業したら長休憩

    for (int i = 0; i < 6; ++i) {
        std::cout << "\n=== セッション開始 ===\n";
        std::cout << "種類: " << session.get_session_name() << '\n';

        int duration_min = session.get_duration_minutes();
        int duration_sec = duration_min * 60;

        std::cout << "時間: " << duration_min << " 分\n";

        PomodoroTimer timer(duration_sec);
        timer.start();

        while (!timer.is_finished()) {
            std::cout << "残り: " << timer.get_remaining_seconds() << " 秒\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "=== セッション終了 ===\n";

        session.next();
    }

    return 0;
}
