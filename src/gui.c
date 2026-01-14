#include <string.h>
#include "raylib.h"
#include "gui.h"
#include "config.h"

GuiInstance *_gui;
void GuiInit(GuiInstance *gui, Config *conf) {
	_gui = gui;

	GuiSetColors(conf->colors);

	_gui->font = LoadFont("resources/go.ttf");
	_gui->font_size = conf->font_size;
	_gui->font_spacing = conf->font_spacing;
}

void GuiUpdate(GuiInstance *gui, float dt) {
	gui->cursor_position = GetMousePosition();
}

void GuiSetColors(Color *colors) {
	memcpy(_gui->colors, colors, sizeof(Color) * COLOR_COUNT * 3);
}

Color GuiFetchColor(u8 state, u8 control) {
	u8 id = COLOR_COUNT * state + control;
	return(_gui->colors[id]);
}

Vector2 TextCenter(Rectangle rec, char *text) {
	Vector2 rec_mid = { rec.x + rec.width * 0.5f, rec.y + rec.height * 0.5f };
	Vector2 text_bounds = MeasureTextEx(_gui->font, text, _gui->font_size, _gui->font_spacing);

	return (Vector2) { rec_mid.x - text_bounds.x * 0.5f, rec_mid.y - text_bounds.y * 0.5f };
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

	Vector2 text_position = TextCenter(rec, text);
	DrawTextEx(_gui->font, text, text_position, _gui->font_size, _gui->font_spacing, GuiFetchColor(state, COLOR_TEXT));

	return (state == BUTTON_PRESSED);
}

