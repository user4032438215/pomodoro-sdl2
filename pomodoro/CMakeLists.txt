cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)  

add_definitions(-DSDL_MAIN_HANDLED)

add_executable(pomodoro
    src/main.cpp

    src/app.cpp

    src/pomodoro_renderer.cpp
    src/pomodoro_timer.cpp
    src/pomodoro_session.cpp
)

target_link_libraries(pomodoro PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf            
)
