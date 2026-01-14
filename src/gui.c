#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "gui.h"
#include "config.h"

ButtonList test_list = (ButtonList) {0};

Color scroll_colors[] = {
	RED,
	GREEN,
	BLUE,
	ORANGE,
	SKYBLUE,
	PURPLE,
	DARKBLUE,
	BROWN,
	BEIGE,
	GRAY,
	RED,
	GREEN,
	BLUE,
	ORANGE,
	SKYBLUE,
	PURPLE,
	DARKBLUE,
	BROWN,
	BEIGE,
	GRAY,
};

GuiInstance *_gui;
void GuiInit(GuiInstance *gui, Config *conf) {
	_gui = gui;

	GuiSetColors(conf->colors);

	_gui->font  = LoadFontEx("resources/go.ttf", 64, 0, 0);
	_gui->font_size = conf->font_size;
	_gui->font_spacing = conf->font_spacing;

	char *test_list_text[] = {
		"entry 01",
		"entry 02",
		"entry 03",
		"entry 04",
		"entry 05",
		"entry 06",
		"entry 07",
		"entry 08",
		"entry 09",
		"entry 10",
		"entry 11",
		"entry 12",
		"entry 13",
		"entry 14",
		"entry 15",
		"entry 16",
		"entry 17",
		"entry 18",
		"entry 19",
		"entry 20",
	};

	test_list = (ButtonList) {
		.text = malloc(sizeof(char*) * 20),
		.position = (Vector2) { 0, 0 },
		.entry_size = (Vector2) { 300, 64 },
		.scroll = 0,
		.count = 20,
		.display_count = 11
	};
	memcpy(test_list.text, test_list_text, sizeof(test_list_text));
}

void GuiUpdate(GuiInstance *gui, float dt) {
	gui->cursor_position = GetMousePosition();

	UpdateButtonList(&test_list);
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

Vector2 TextCenterEx(Rectangle rec, char *text, float font_size, float font_spacing) {
	Vector2 rec_mid = { rec.x + rec.width * 0.5f, rec.y + rec.height * 0.5f };
	Vector2 text_bounds = MeasureTextEx(_gui->font, text, font_size, font_spacing);

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

bool ButtonEx(Rectangle rec, char *text, i8 icon, float font_size, float font_spacing) {
	u8 state = BUTTON_DEFAULT;

	if(CheckCollisionPointRec(_gui->cursor_position, rec)) {
		state = BUTTON_HOVERED;
			
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			state = BUTTON_PRESSED;
	}

	DrawRectangleRec(rec, GuiFetchColor(state, COLOR_BACKGROUND));
	DrawRectangleLinesEx(rec, 2, GuiFetchColor(state, COLOR_BORDER));

	Vector2 text_position = TextCenterEx(rec, text, font_size, font_spacing);
	DrawTextEx(_gui->font, text, text_position, font_size, font_spacing, GuiFetchColor(state, COLOR_TEXT));

	return (state == BUTTON_PRESSED);
}

void UpdateButtonList(ButtonList *button_list) {
	if(IsKeyPressed(KEY_UP))
		button_list->scroll = (int)(button_list->scroll - 1) % button_list->count;

	if(IsKeyPressed(KEY_DOWN))
		button_list->scroll = (int)(button_list->scroll + 1) % button_list->count;

	u16 start_id = (button_list->scroll);
	u16 center = button_list->display_count >> 1;

	float y = button_list->position.y;

	for(u16 i = 0; i < button_list->display_count; i++) {
		float height_mod = (fabsf((float)(center) - i)) * 5;

		Rectangle rec = (Rectangle) {
			.x = button_list->position.x, 
			.y = y,
			.width = button_list->entry_size.x,
			.height = button_list->entry_size.y - height_mod	
		};

		y += rec.height;

		u16 id = (start_id + i) % button_list->count;

		float font_size = (_gui->font_size / (height_mod * 0.055f));
		if(i == center) font_size = _gui->font_size;
		font_size = Clamp(font_size, 1, _gui->font_size);

		ButtonEx(rec, button_list->text[id], 0, font_size, _gui->font_spacing);
		DrawCircleV((Vector2) {rec.x + rec.width - 35, (rec.y + rec.height * 0.5f) }, rec.height * 0.45f, ColorAlpha(scroll_colors[id], 0.5f));
		DrawRectangleRec(rec, ColorAlpha(BLACK, height_mod * 0.025f));
	}
}

