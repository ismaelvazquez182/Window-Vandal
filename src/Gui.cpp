#pragma once

#include "Gui.h"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#pragma warning(disable : 4996) // Raygui uses deprecated functions
#include "raygui.h"


Gui::Gui()
{
	SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	InitWindow(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, m_WINDOW_TITLE);
	SetTargetFPS(60);
	GuiLoadStyle(m_STYLE);

	SetWindowPosition(static_cast<int>(m_window_position_x), static_cast<int>(m_window_position_y));

	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
	GuiSetStyle(DEFAULT, TEXT_SPACING, 2);
}

Gui::~Gui()
{
	CloseWindow();
}

void Gui::Run(void (*refresh)(std::string *), void (*changeTitle)(int, std::string))
{

	refresh(m_list_items);

	while (!WindowShouldClose() && !m_is_window_should_close) {
		Vector2 temp = GetMousePosition();
		m_mouse_position_x = temp.x;
		m_mouse_position_y = temp.y;

		checkIfWindowShouldBeDragged();
		moveWindow();

		BeginDrawing();
		ClearBackground(DARKGRAY);
		m_is_window_should_close = GuiWindowBox({ 0, 0, static_cast<float>(m_WINDOW_WIDTH),static_cast<float>(m_WINDOW_HEIGHT) }, "#152# Window Vandal");

		Vector2 temp2 = { m_scroll_x, m_scroll_y };
		GuiScrollPanel({m_LIST_BOUNDS_X, m_LIST_BOUNDS_Y, m_LIST_BOUNDS_WIDTH, m_LIST_BOUNDS_HEIGHT }, NULL, { 0, 0, 180, static_cast<float>(m_item_count) * m_BUTTON_HEIGHT }, &temp2, NULL); // height = numItems * rowHeight
		m_scroll_x = temp2.x;
		m_scroll_y = temp2.y;

		// Use scissor mode to clip drawing inside panel
		BeginScissorMode(m_LIST_BOUNDS_X, m_LIST_BOUNDS_Y, m_LIST_BOUNDS_WIDTH, m_LIST_BOUNDS_HEIGHT);

		int visible_items = m_LIST_BOUNDS_HEIGHT / m_BUTTON_HEIGHT;
		int first_visible = (int)(-m_scroll_y / m_BUTTON_HEIGHT);
		int last_visible = first_visible + visible_items + 1;

		if (last_visible > m_item_count) last_visible = m_item_count;

		GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		// Draw the buttons
		for (int i = first_visible; i < last_visible; i++) {
			Rectangle item_bounds = { m_LIST_BOUNDS_X + 2, m_LIST_BOUNDS_Y + (i * m_BUTTON_HEIGHT) + (int)m_scroll_y, m_LIST_BOUNDS_WIDTH - 4, m_BUTTON_HEIGHT };
			if (GuiButton(item_bounds, m_list_items[i].c_str())) {
				m_active = i;
				std::string temp = m_list_items[i];
				temp.erase(0, 3);
				strcpy_s(m_new_window_title, 256, temp.c_str());
			}
			
		}

		EndScissorMode();

		GuiTextBox({10, 550, 500, 40 }, m_new_window_title, 256, true);
		GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

		if (GuiButton({ 520, 550, 150, 40 }, "Change Title")) {

			if (m_active >= 0) {
				changeTitle(m_active, m_new_window_title);
				m_active = -1;
				refresh(m_list_items);
				strcpy_s(m_new_window_title, 256, "");
			}
		}

		if (GuiButton({ 680, 550, 110, 40 }, "Refresh")) {
			refresh(m_list_items);
		}

		EndDrawing();
	}
}

void Gui::checkIfWindowShouldBeDragged()
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_is_window_being_dragged)
	{
		if (CheckCollisionPointRec({m_mouse_position_x, m_mouse_position_y}, { 0, 0, static_cast<float>(m_WINDOW_WIDTH), 20 }))
		{
			Vector2 temp = GetWindowPosition();
			m_window_position_x = temp.x;
			m_window_position_y = temp.y;
			m_is_window_being_dragged = true;
			m_pan_offset_x = m_mouse_position_x;
			m_pan_offset_y = m_mouse_position_y;
		}
	}
}

void Gui::moveWindow()
{
	if (m_is_window_being_dragged)
	{
		m_window_position_x += (m_mouse_position_x - m_pan_offset_x);
		m_window_position_y += (m_mouse_position_y - m_pan_offset_y);

		SetWindowPosition(static_cast<int>(m_window_position_x), static_cast<int>(m_window_position_y));

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) m_is_window_being_dragged = false;
	}
}