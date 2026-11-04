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

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/settings.json
    ${CMAKE_BINARY_DIR}/settings.json
    COPYONLY
)

add_custom_command(
    TARGET pomodoro POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/fonts
        $<TARGET_FILE_DIR:pomodoro>/fonts
)

if (WIN32)
    target_compile_definitions(pomodoro PRIVATE
        SDL_MAIN_HANDLED
    )
endif()

enable_testing()

add_executable(timer_tests
    tests/timer_tests.cpp
    src/pomodoro_timer.cpp
)

target_include_directories(timer_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_test(
    NAME timer_tests
    COMMAND timer_tests
)

add_executable(session_tests
    tests/session_tests.cpp
    src/pomodoro_session.cpp
    src/settings.cpp
)

target_include_directories(session_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(session_tests PRIVATE
    nlohmann_json::nlohmann_json
)

add_test(
    NAME session_tests
    COMMAND session_tests
)

add_executable(settings_tests
    tests/settings_tests.cpp
    src/settings.cpp
)

target_include_directories(settings_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(settings_tests PRIVATE
    nlohmann_json::nlohmann_json
)


add_test(
    NAME settings_tests
    COMMAND settings_tests
)

add_executable(button_tests
    tests/button_tests.cpp
    src/button.cpp
    src/pomodoro_renderer.cpp
)

target_include_directories(button_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(button_tests PRIVATE
    SDL_MAIN_HANDLED
)

target_link_libraries(button_tests PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)

add_test(
    NAME button_tests
    COMMAND button_tests
)