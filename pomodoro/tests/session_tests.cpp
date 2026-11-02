// session_tests.cpp
#include "pomodoro_session.hpp"
#include "settings.hpp"

#include <cassert>
#include <iostream>

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

    void test_session_work_to_short_break()
    {
        Settings settings;
        PomodoroSession session(settings);

        session.next();

        assert(session.get_type() == SessionType::SHORT_BREAK);
        assert(session.get_duration_minutes() == 5);

        session.next();

        assert(session.get_type() == SessionType::WORK);

        std::cout << "[PASS] session work to short break\n";
    }

    /*
        void test_session_long_break()
    {
        Settings settings;
        PomodoroSession session(settings);

        for (int i = 0; i < 3; ++i) {
            session.next();
            assert(session.get_type() == SessionType::SHORT_BREAK);

            session.next();
            assert(session.get_type() == SessionType::WORK);
        }

        session.next();
        assert(session.get_type() == SessionType::LONG_BREAK);

        assert(session.get_duration_minutes() == 15);
        assert(session.get_type() == SessionType::LONG_BREAK);

        std::cout << "[PASS] session long break\n";
    }
    */
    void test_session_long_break()
    {
        Settings settings;
        PomodoroSession session(settings);

        // 1stWORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 2ndWORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);

        // 3rdWORK -> SHORT_BREAK
        session.next();
        assert(session.get_type() == SessionType::SHORT_BREAK);

        // SHORT_BREAK -> WORK
        session.next();
        assert(session.get_type() == SessionType::WORK);


        // 4thWORK -> LONG_BREAK
        session.next();
        assert(session.get_type() == SessionType::LONG_BREAK);
        assert(session.get_duration_minutes() == 15);
        assert(session.get_session_name() == "Long Break");

        std::cout << "[PASS] session long break\n";
    }



    void test_session_reset()
    {
        Settings settings;
        PomodoroSession session(settings);

        session.next();
        session.next();
        session.reset();

        assert(session.get_type() == SessionType::WORK);
        assert(session.completed_work_sessions() == 0);

        std::cout << "[PASS] session reset\n";
    }

    void test_session_uses_updated_settings()
    {
        Settings settings;
        PomodoroSession session(settings);

        PomodoroConfig draft;
        draft.work_minutes = 40;

        assert(settings.apply(draft));

        assert(session.get_duration_minutes() == 40);

        std::cout << "[PASS] session uses updated settings\n";
    }
}

int main()
{
    test_session_initial_state();
    test_session_work_to_short_break();
    test_session_long_break();
    test_session_reset();
    test_session_uses_updated_settings();

    std::cout << "\nAll session tests passed.\n";

    return 0;
}