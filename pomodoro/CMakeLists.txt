cmake_minimum_required(VERSION 3.22)

project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(pomodoro
    src/main.cpp
    src/app.cpp
    src/pomodoro_renderer.cpp
    src/pomodoro_timer.cpp
    src/pomodoro_session.cpp
    src/settings.cpp
    src/button.cpp
)

target_include_directories(pomodoro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(pomodoro PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    nlohmann_json::nlohmann_json
)

# settings.jsonを実行ファイルと同じフォルダへコピーする
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/settings.json
    ${CMAKE_BINARY_DIR}/settings.json
    COPYONLY
)

if (WIN32)
    target_compile_definitions(pomodoro PRIVATE
        SDL_MAIN_HANDLED
    )
endif()

enable_testing()

add_executable(pomodoro_tests
    tests/timer_session_tests.cpp

    src/app.cpp
    src/pomodoro_timer.cpp
    src/pomodoro_session.cpp
    src/settings.cpp
    src/pomodoro_renderer.cpp
    src/button.cpp
)

target_include_directories(pomodoro_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(pomodoro_tests PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    nlohmann_json::nlohmann_json
)

add_test(
    NAME pomodoro_tests
    COMMAND pomodoro_tests
)