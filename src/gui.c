#include <string.h>
#include "raylib.h"
#include "gui.h"
#include "config.h"

GuiInstance *_gui;
void GuiInit(GuiInstance *gui, Color *colors) {
	_gui = gui;
	GuiSetColors(_gui, colors);
}

void GuiUpdate(GuiInstance *gui, float dt) {
	gui->cursor_position = GetMousePosition();

	for(u8 i = 0; i < COLOR_COUNT; i++) {
		DrawRectangle(i * (64 + 10), 64, 64, 64, _gui->colors[i]);
		DrawRectangle(i * (64 + 10), 64 * 2, 64, 64, _gui->colors[i + (COLOR_COUNT)]);
		DrawRectangle(i * (64 + 10), 64 * 3, 64, 64, _gui->colors[i + (COLOR_COUNT * 2)]);
	}
}

void GuiSetColors(GuiInstance *gui, Color *colors) {
	memcpy(gui->colors, colors, sizeof(Color) * COLOR_COUNT * 3);
}

Color GuiFetchColor(u8 state, u8 control) {
	u8 id = COLOR_COUNT * state + control;
	return(_gui->colors[id]);
}

bool Button(Rectangle rec, char *text, i8 icon) {
	u8 state = BUTTON_DEFAULT;

	if(CheckCollisionPointRec(_gui->cursor_position, rec)) {
		state = BUTTON_HOVERED;
			
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			state = BUTTON_PRESSED;
	}

	DrawRectangleRec(rec, GuiFetchColor(state, COLOR_BACKGROUND));
	DrawRectangleLinesEx(rec, 2, GuiFetchColor(state, COLOR_BORDER));

	return (state == BUTTON_PRESSED);
}

