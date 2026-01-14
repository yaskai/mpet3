#include "raylib.h"
#include "ktypes.h"
#include "config.h"

#ifndef GUI_H_
#define GUI_H_

enum BUTTON_STATES : u8 {
	BUTTON_DEFAULT = 0,
	BUTTON_HOVERED = 1,
	BUTTON_PRESSED = 2
};

typedef struct {
	Font font;

	Color colors[12];

	Vector2 cursor_position;

	u32 font_size;
	u32 font_spacing;

} GuiInstance;

void GuiInit(GuiInstance *gui, Config *conf);
void GuiUpdate(GuiInstance *gui, float dt);

void GuiSetColors(Color *colors);
Color GuiFetchColor(u8 state, u8 control);

Vector2 TextCenter(Rectangle rec, char *text);

bool Button(Rectangle rec, char *text, i8 icon);

#endif
