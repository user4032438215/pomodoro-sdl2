// settings_tests.cpp
#include "settings.hpp"

#include <cassert>
#include <iostream>

void test_settings_initial_state()
{
    Settings settings;

    assert(settings.current().work_minutes == 25);
    assert(settings.current().short_break_minutes == 5);
    assert(settings.current().long_break_minutes == 15);
    assert(settings.current().long_break_interval == 4);

    std::cout << "[PASS] settings initial state\n";
}

void test_settings_apply_valid_draft()
{
    Settings settings;

    PomodoroConfig draft;
    draft.work_minutes = 40;

    assert(settings.apply(draft));
    assert(settings.current().work_minutes == 40);

    std::cout << "[PASS] settings apply valid draft\n";
}

void test_settings_apply_invalid_draft()
{
    Settings settings;

    PomodoroConfig draft;
    draft.work_minutes = 999;

    assert(!settings.apply(draft));
    assert(settings.current().work_minutes == 25);

    std::cout << "[PASS] settings apply invalid draft\n";
}

void test_settings_defaults()
{
    Settings settings;

    PomodoroConfig draft;
    draft.work_minutes = 40;

    settings.apply(draft);

    draft = settings.defaults();

    assert(draft.work_minutes == 25);
    assert(draft.short_break_minutes == 5);
    assert(draft.long_break_minutes == 15);
    assert(draft.long_break_interval == 4);

    std::cout << "[PASS] settings defaults\n";
}

int main()
{
    std::cout << "Running settings tests...\n\n";

    test_settings_initial_state();
    test_settings_apply_valid_draft();
    test_settings_apply_invalid_draft();
    test_settings_defaults();

    std::cout << "\nAll settings tests passed.\n";

    return 0;
}