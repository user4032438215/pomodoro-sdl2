//main.cpp
#include "app.hpp"

#include <iostream>

int main()
{
    App app;

    if (!app.init()) {
        std::cerr << "Application initialization failed.\n";
        return 1;
    }

    app.run();

    return 0;
}