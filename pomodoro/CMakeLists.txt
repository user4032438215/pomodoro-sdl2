cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG REQUIRED)

add_executable(pomodoro
    pomodoro/pomodoro.cpp
)

target_link_libraries(pomodoro PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
)
