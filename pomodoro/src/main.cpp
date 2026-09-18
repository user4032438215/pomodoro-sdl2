#include "pomodoro_session.hpp"
#include "pomodoro_timer.hpp"

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace
{
    void test_session_initial_state()
    {
        PomodoroSession session(
            4,   // long break interval
            25,  // work minutes
            5,   // short break minutes
            15   // long break minutes
        );

        assert(session.get_type() == SessionType::WORK);
        assert(session.get_duration_minutes() == 25);
        assert(session.get_session_name() == "Work");
        assert(!session.should_take_long_break());

        std::cout << "[PASS] session initial state\n";
    }

    void test_session_transition()
    {
        PomodoroSession session(
            4,
            25,
            5,
            15
        );

        // 1回目の作業終了: 短い休憩
        session.next();

        assert(session.get_type() == SessionType::SHORT_BREAK);
        assert(session.get_duration_minutes() == 5);
        assert(session.get_session_name() == "Short Break");

        // 短い休憩終了: 作業
        session.next();

        assert(session.get_type() == SessionType::WORK);
        assert(session.get_duration_minutes() == 25);

        std::cout << "[PASS] session work/short-break transition\n";
    }

    void test_session_long_break()
    {
        PomodoroSession session(
            4,
            25,
            5,
            15
        );

        // 1回目: WORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 2回目: WORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 3回目: WORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 4回目: WORK -> LONG_BREAK
        session.next();

        assert(session.get_type() == SessionType::LONG_BREAK);
        assert(session.get_duration_minutes() == 15);
        assert(session.get_session_name() == "Long Break");
        assert(session.should_take_long_break());

        std::cout << "[PASS] session long-break transition\n";
    }

    void test_session_reset()
    {
        PomodoroSession session(
            4,
            25,
            5,
            15
        );

        session.next();
        session.next();

        assert(session.get_type() == SessionType::WORK);

        session.reset();

        assert(session.get_type() == SessionType::WORK);
        assert(session.get_duration_minutes() == 25);
        assert(!session.should_take_long_break());

        std::cout << "[PASS] session reset\n";
    }

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
        assert(!timer.is_finished());

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        timer.update();

        assert(timer.get_state() == TimerState::FINISHED);
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

        assert(timer.get_state() == TimerState::PAUSED);
        assert(!timer.is_finished());

        const int remaining_while_paused =
            timer.get_remaining_seconds();

        // 一時停止中は時間が進まないことを確認
        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        const int remaining_after_wait =
            timer.get_remaining_seconds();

        assert(
            remaining_after_wait == remaining_while_paused
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

        const int remaining_while_paused =
            timer.get_remaining_seconds();

        timer.resume();

        assert(timer.get_state() == TimerState::RUNNING);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        timer.update();

        assert(timer.get_state() == TimerState::FINISHED);
        assert(timer.get_remaining_seconds() == 0);
        assert(remaining_while_paused >= 0);

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
        assert(!timer.is_finished());
        assert(timer.get_remaining_seconds() == 3);
        assert(timer.get_progress() == 0.0f);

        std::cout << "[PASS] timer reset\n";
    }

    void test_timer_invalid_duration()
    {
        PomodoroTimer timer(-10);

        // 現在の実装では負数を0として扱う
        assert(timer.get_remaining_seconds() == 0);
        assert(timer.get_progress() == 1.0f);

        std::cout << "[PASS] timer invalid duration handling\n";
    }

    void test_timer_progress()
    {
        PomodoroTimer timer(2);

        timer.start();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        const float progress = timer.get_progress();

        // 1秒経過したので、進捗はおおむね50%以上
        assert(progress >= 0.45f);
        assert(progress <= 1.0f);

        std::cout << "[PASS] timer progress\n";
    }
}

int main()
{
    std::cout << "Running Pomodoro tests...\n\n";

    test_session_initial_state();
    test_session_transition();
    test_session_long_break();
    test_session_reset();

    test_timer_initial_state();
    test_timer_start_and_finish();
    test_timer_pause();
    test_timer_resume();
    test_timer_reset();
    test_timer_invalid_duration();
    test_timer_progress();

    std::cout << "\nAll tests passed.\n";

    return 0;
}