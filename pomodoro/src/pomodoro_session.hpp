//pomodoro_session.hpp
#pragma once
#include "settings.hpp"
#include <string>

// PomodoroSessionが管理するのは、現在のセッション種別 と作業セッションの完了回数 の 2種のみ

enum class SessionType {
    WORK,
    SHORT_BREAK,
    LONG_BREAK
};

class PomodoroSession {
public:
    explicit PomodoroSession(const Settings& settings);

    void next();
    void reset();

    SessionType get_type() const noexcept;
    int get_duration_minutes() const;
    std::string get_session_name() const;

    bool should_take_long_break() const;

    int completed_work_sessions() const noexcept; //代わりに追加

private:
    // ☆ 設定値のコピーを持たない
    const Settings& settings_;

    // ☆ これらはセッションの状態
    int completed_work_sessions_{ 0 };
    SessionType current_{ SessionType::WORK };

};
