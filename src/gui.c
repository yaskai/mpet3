#include <math.h>
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
		.entry_size = (Vector2) { 200, 64 },
		.scroll = 0,
		.count = 20,
		.display_count = 11
	};
	memcpy(test_list.text, test_list_text, sizeof(test_list_text));

	u16 center = test_list.display_count >> 1;
	float y = 0;

	for(u16 i = 0; i < test_list.display_count; i++) {
		float height_mod = (fabsf((float)(center) - i)) * 5;
		y += test_list.entry_size.y - height_mod;
	}

	test_list.render_target = LoadRenderTexture(test_list.entry_size.x, y);
}

void GuiUpdate(GuiInstance *gui, float dt) {
	gui->cursor_position = GetMousePosition();

	//UpdateButtonList(&test_list, dt);
	
	float w = test_list.render_target.texture.width;
	float h = test_list.render_target.texture.height;
	DrawTexturePro(
		test_list.render_target.texture,
		(Rectangle){0, 0, w, -h},
		(Rectangle){0, 0, w, h},
		(Vector2) { 0, 0 },
		0,
		WHITE
	);
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

bool ButtonEx(Rectangle rec, char *text, i8 icon, float font_size, float font_spacing, float alpha) {
	u8 state = BUTTON_DEFAULT;

	if(CheckCollisionPointRec(_gui->cursor_position, rec)) {
		state = BUTTON_HOVERED;
			
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			state = BUTTON_PRESSED;
	}

	DrawRectangleRec(rec, GuiFetchColor(state, COLOR_BACKGROUND));
	DrawRectangleLinesEx(rec, 2, GuiFetchColor(state, COLOR_BORDER));

	Rectangle hightlight_top = (Rectangle) { 
		.x = rec.x + 2,
		.y = rec.y,
		.width = rec.width - 4,
		.height = rec.height * 0.1f
	};
	DrawRectangleRec(hightlight_top, ColorAlpha(GuiFetchColor(state, COLOR_FOREGROUND), alpha));

	Rectangle shadow_bot = (Rectangle) {
		.x = rec.x + 2,
		.y = rec.y + rec.height - (rec.height * 0.1f), 
		.width = rec.width - 4,
		.height = rec.height * 0.1f
	};
	DrawRectangleRec(shadow_bot, ColorAlpha(BLACK, 0.25f * alpha));

	Vector2 text_position = TextCenterEx(rec, text, font_size, font_spacing);
	DrawTextEx(_gui->font, text, text_position, font_size, font_spacing, ColorAlpha(GuiFetchColor(state, COLOR_TEXT), alpha));

	return (state == BUTTON_PRESSED);
}

void UpdateButtonList(ButtonList *button_list, float dt) {
	/*
	if(IsKeyPressed(KEY_UP))
		button_list->scroll = (int)(button_list->scroll - 1 + button_list->count) % button_list->count;

	if(IsKeyPressed(KEY_DOWN))
		button_list->scroll = (int)(button_list->scroll + 1) % button_list->count;
	*/

	float wheel = GetMouseWheelMove();

	if(fabsf(wheel) > 0) {
		button_list->scroll_dir = (wheel < 0) ? -1 : 1;
		button_list->offset += 2 * wheel * dt;
	}

	if(wheel == 0 && fabsf(button_list->offset) > 0) {
		button_list->offset = Lerp(button_list->offset, copysignf(1 + 0.5f, button_list->scroll_dir), dt);	
	}

	if(button_list->offset <= -1) {
		button_list->scroll = (int)(button_list->scroll + 1) % button_list->count;
		button_list->offset = 0;
	} else if(button_list->offset >= 1) {
		button_list->scroll = (int)(button_list->scroll - 1 + button_list->count) % button_list->count;
		button_list->offset = 0;
	} 

	u16 start_id = (button_list->scroll);
	u16 center = button_list->display_count >> 1;

	float y = button_list->position.y;

	BeginTextureMode(button_list->render_target);
	ClearBackground(BLACK);

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

		float font_size = (_gui->font_size / (height_mod * 0.085f));
		if(i == center) font_size = _gui->font_size;
		font_size = Clamp(font_size, 1, _gui->font_size);

		float a = (i == center) ? 1 : (10 / (button_list->entry_size.y - rec.height));  

		if(button_list->offset != 0) rec.y += (button_list->offset * i);
		//ButtonEx(rec, button_list->text[id], 0, font_size, _gui->font_spacing, a);
		//DrawRectangleRec(rec, ColorAlpha(BLACK, height_mod * 0.025f));

		//DrawText(TextFormat("%f", a), rec.x, rec.y, 32, WHITE);

		DrawCircleV(
			(Vector2) {rec.x + rec.width - 64, (rec.y + rec.height * 0.5f) + (button_list->offset * rec.height) },
			rec.height * 0.25f,
			ColorAlpha(scroll_colors[id], a)
		);
	}

	EndTextureMode();
}

void TestUpdateButtonList(float dt) {
	UpdateButtonList(&test_list, dt);
}

