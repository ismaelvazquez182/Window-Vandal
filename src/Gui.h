#pragma once

#include <string>

class Gui
{
public:
	Gui();
	~Gui();
	void Run(void (*)(std::string*), void (*)(int, std::string));

private:
	const char* m_WINDOW_TITLE{ "Window Vandal" };
	const char* m_STYLE{ "C:/raygui/styles/dark/style_dark.rgs" };
	const int m_WINDOW_WIDTH{ 800 };
	const int m_WINDOW_HEIGHT{ 600 };
	float m_LIST_BOUNDS_WIDTH{ 780 }; // m_WINDOW_WIDTH - (m_LIST_BOUNDS_X * 2)
	float m_LIST_BOUNDS_HEIGHT{ 500 }; // 500 + 20 + 35 = 555
	float m_LIST_BOUNDS_X{ 10 };
	float m_LIST_BOUNDS_Y{ 35 }; // 20 + (m_LIST_BOUNDS_X * 1.5)

	bool m_is_window_should_close{ false };
	bool m_is_window_being_dragged{ false };

	float m_mouse_position_x{ 0 };
	float m_mouse_position_y{ 0 };

	float m_window_position_x{ 500 };
	float m_window_position_y{ 200 };

	float m_pan_offset_x{ 0 };
	float m_pan_offset_y{ 0 };

	int m_item_count{ 50 };
	int m_active{ -1 };
	int m_focus{ -1 };

	float m_scroll_x{ 0 };
	float m_scroll_y{ 0 };

	const float m_BUTTON_HEIGHT{ 40 };

	char m_new_window_title[256];
	std::string m_list_items[256];

private:
	void checkIfWindowShouldBeDragged();
	void moveWindow();
};