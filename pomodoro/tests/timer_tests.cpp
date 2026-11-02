// timer_tests.cpp
#include "pomodoro_timer.hpp"

#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

namespace
{
    void test_timer_initial_state()
    {
        PomodoroTimer timer(2);

        assert(timer.get_state() == TimerState::IDLE);
        assert(!timer.is_finished());
        assert(timer.get_remaining_seconds() == 2);
        assert(timer.get_progress() == 0.0f);

        std::cout << "[PASS] timer initial state\n";
    }

    void test_timer_start_and_finish()
    {
        PomodoroTimer timer(1);

        timer.start();

        assert(timer.get_state() == TimerState::RUNNING);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        timer.update();

        assert(timer.is_finished());
        assert(timer.get_remaining_seconds() == 0);
        assert(timer.get_progress() == 1.0f);

        std::cout << "[PASS] timer start and finish\n";
    }

    void test_timer_pause()
    {
        PomodoroTimer timer(2);

        timer.start();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        timer.pause();

        const int remaining_while_paused =
            timer.get_remaining_seconds();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        assert(
            timer.get_remaining_seconds() ==
            remaining_while_paused
        );

        std::cout << "[PASS] timer pause\n";
    }

    void test_timer_resume()
    {
        PomodoroTimer timer(2);

        timer.start();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        timer.pause();

        timer.resume();

        assert(timer.get_state() == TimerState::RUNNING);

        std::cout << "[PASS] timer resume\n";
    }

    void test_timer_reset()
    {
        PomodoroTimer timer(1);

        timer.start();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        timer.update();

        assert(timer.is_finished());

        timer.reset(3);

        assert(timer.get_state() == TimerState::IDLE);
        assert(timer.get_remaining_seconds() == 3);
        assert(timer.get_progress() == 0.0f);

        std::cout << "[PASS] timer reset\n";
    }

    void test_timer_invalid_duration()
    {
        PomodoroTimer timer(-10);

        assert(timer.get_remaining_seconds() == 1);

        timer.reset(0);

        assert(timer.get_remaining_seconds() == 1);

        std::cout << "[PASS] timer invalid duration\n";
    }

    void test_timer_idle_does_not_count_down()
    {
        PomodoroTimer timer(2);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        assert(timer.get_state() == TimerState::IDLE);
        assert(timer.get_remaining_seconds() == 2);

        std::cout << "[PASS] idle timer does not count down\n";
    }
}

int main()
{
    test_timer_initial_state();
    test_timer_start_and_finish();
    test_timer_pause();
    test_timer_resume();
    test_timer_reset();
    test_timer_invalid_duration();
    test_timer_idle_does_not_count_down();

    std::cout << "\nAll timer tests passed.\n";

    return 0;
}