
// button_tests.cpp
#include "button.hpp"

#include <cassert>
#include <iostream>

void test_button_contains_inside_point()
{
    Button button{
        { 100, 100, 50, 40 },
        "TEST"
    };

    assert(button.contains_point(100, 100));
    assert(button.contains_point(120, 120));
    assert(button.contains_point(149, 139));

    std::cout
        << "[PASS] button contains inside point\n";
}

void test_button_rejects_outside_point()
{
    Button button{
        { 100, 100, 50, 40 },
        "TEST"
    };

    assert(!button.contains_point(99, 100));
    assert(!button.contains_point(150, 100));
    assert(!button.contains_point(100, 99));
    assert(!button.contains_point(100, 140));

    std::cout
        << "[PASS] button rejects outside point\n";
}

void test_button_label()
{
    Button button{
        { 100, 100, 50, 40 },
        "START"
    };

    assert(button.label() == "START");

    button.set_label("PAUSE");

    assert(button.label() == "PAUSE");

    std::cout << "[PASS] button label\n";
}

int main()
{
    test_button_contains_inside_point();
    test_button_rejects_outside_point();
    test_button_label();

    std::cout << "\nAll button tests passed.\n";

    return 0;
}

// minimum button_tests.cpp
/*
#include "button.hpp"

#include <cassert>
#include <iostream>

int main()
{
    std::cout << "button tests\n";
    return 0;
}
*/

