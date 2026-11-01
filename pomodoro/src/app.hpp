//app.hpp
#pragma once

#include "pomodoro_timer.hpp"
#include "pomodoro_session.hpp"
#include "pomodoro_renderer.hpp"
#include "settings.hpp"

#include "button.hpp"

#include <SDL2/SDL.h> 

enum class AppScreen
{
	TIMER,
	SETTINGS
};

class App {
public:
	App();

	bool init();
	void run();

	//added for tests
	TimerState timer_state() const noexcept;
	SessionType session_type() const noexcept;
	int remaining_seconds() const;
	float progress() const;

	std::string button_label() const;

private:
	void handle_events();
	void update();
	void render();
	void render_timer_screen();
	void render_settings_screen();

	/*
		bool is_inside(
		const SDL_Rect& rect,
		int x,
		int y
	) const;
	*/


	void start_current_session();
	void reset_current_timer();
	void start_current_timer();

	// settings_を最初に宣言する
	// PomodoroSessionがSettingsを参照するため
	Settings settings_;

	PomodoroSession session_;
	PomodoroTimer timer_;
	PomodoroRenderer renderer_;

	bool running_{ true };

	//設定画面で編集中の値 を 入れる メンバ
	PomodoroConfig settings_draft_{};

	//TIMER screen buttons
	//
	Button start_button_{
	{ 270, 330, 100, 40 },
	"START"
	};

	Button reset_button_{
	{ 150, 330, 100, 40 },
	"RESET"
	};

	Button settings_button_{
	{ 390, 330, 100, 40 },
	"SETTINGS"
	};

	//SETTINGS screen buttons
	//stteper
	Button work_minus_button_{
	{ 180, 150, 40, 40 },
	"-"
	};
	Button work_plus_button_{
	{ 560, 150, 40, 40 },
	"+"
	};

	Button short_break_minus_button_{
	{ 180, 190, 40, 40 },
	"-"
	};
	Button short_break_plus_button_{
	{ 560, 190, 40, 40 },
	"+"
	};

	Button long_break_minus_button_{
	{ 180, 230, 40, 40 },
	"-"
	};
	Button long_break_plus_button_{
	{ 560, 230, 40, 40 },
	"+"
	};

	Button long_break_interval_minus_button_{
	{ 180, 270, 40, 40 },
	"-"
	};
	Button long_break_interval_plus_button_{
	{ 560, 270, 40, 40 },
	"+"
	};

	//
	Button back_button_{
	{ 150, 400, 100, 40 },
	"BACK"
	};
	
	Button save_button_{
	{ 270, 400, 100, 40 },
	"SAVE"
	};

	Button defaults_button_{
	{ 390, 400, 100, 40 },
	"DEFAULTS"
	};

	AppScreen screen_{ AppScreen::TIMER };
};