//timer_session_tests.cpp

#include "pomodoro_session.hpp"
#include "pomodoro_timer.hpp"
#include "settings.hpp"

//#include "app.hpp"

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace
{
    void test_session_initial_state()
    {
        Settings settings;
        PomodoroSession session(settings);

        assert(session.get_type() == SessionType::WORK);
        assert(session.get_duration_minutes() == 25);
        assert(session.get_session_name() == "Work");
        assert(!session.should_take_long_break());

        std::cout << "[PASS] session initial state\n";
    }

    void test_session_transition()
    {
        Settings settings;
        PomodoroSession session(settings);

        // WORK -> SHORT_BREAK
        session.next();

        assert(session.get_type() == SessionType::SHORT_BREAK);
        assert(session.get_duration_minutes() == 5);
        assert(session.get_session_name() == "Short Break");

        // SHORT_BREAK -> WORK
        session.next();

        assert(session.get_type() == SessionType::WORK);
        assert(session.get_duration_minutes() == 25);

        std::cout << "[PASS] session work/short-break transition\n";
    }

    void test_session_long_break()
    {
        Settings settings;
        PomodoroSession session(settings);

        // 1回目: WORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 2回目
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 3回目
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

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
        Settings settings;
        PomodoroSession session(settings);

        session.next();
        session.next();

        assert(session.get_type() == SessionType::WORK);

        session.reset();

        assert(session.get_type() == SessionType::WORK);
        assert(session.get_duration_minutes() == 25);
        assert(!session.should_take_long_break());
        assert(session.completed_work_sessions() == 0);

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

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        const int remaining_after_wait =
            timer.get_remaining_seconds();

        // ☆ PAUSED中は残り時間が変わらない
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
        assert(timer.is_finished());
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

        // ☆ 負数は1秒に補正される
        assert(timer.get_remaining_seconds() == 1);
        assert(timer.get_progress() == 0.0f);

        timer.reset(0);

        // ☆ 0秒も1秒に補正される
        assert(timer.get_remaining_seconds() == 1);
        assert(timer.get_progress() == 0.0f);

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

        assert(progress >= 0.45f);
        assert(progress <= 1.0f);

        std::cout << "[PASS] timer progress\n";
    }

    //added
    void test_timer_initial_state_does_not_count_down()
    {
        PomodoroTimer timer(2);

        // Arrange
        assert(timer.get_state() == TimerState::IDLE);
        assert(timer.get_remaining_seconds() == 2);
        assert(timer.get_progress() == 0.0f);

        // Act
        std::this_thread::sleep_for(
            std::chrono::milliseconds(1100)
        );

        // Assert
        assert(timer.get_state() == TimerState::IDLE);
        assert(timer.get_remaining_seconds() == 2);
        assert(timer.get_progress() == 0.0f);

        std::cout
            << "[PASS] idle timer does not count down\n";
    }

    //void test_app_initial_state()
    //{
    //    App app;

    //    assert(app.init());

    //    assert(app.timer_state() == TimerState::IDLE);
    //    assert(app.session_type() == SessionType::WORK);
    //    assert(app.remaining_seconds() == 25 * 60);
    //    assert(app.progress() == 0.0f);

    //    std::cout << "[PASS] app initial state\n";
    //}


}

int main()
{
    std::cout << "Running Pomodoro tests...\n\n";

    test_session_initial_state();
    test_session_transition();
    test_session_long_break();
    test_session_reset();

    test_timer_initial_state();

    //added
    test_timer_initial_state_does_not_count_down();

    test_timer_start_and_finish();
    test_timer_pause();
    test_timer_resume();
    test_timer_reset();
    test_timer_invalid_duration();
    test_timer_progress();

    std::cout << "\nAll tests passed.\n";

    return 0;
}