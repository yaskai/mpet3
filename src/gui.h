#include "ktypes.h"
#include "raylib.h"

#ifndef GUI_H_
#define GUI_H_

enum BUTTON_STATES : u8 {
	BUTTON_DEFAULT = 0,
	BUTTON_HOVERED = 1,
	BUTTON_PRESSED = 2
};

typedef struct {
	Color colors[12];

	Vector2 cursor_position;

} GuiInstance;

void GuiInit(GuiInstance *gui, Color *colors);
void GuiUpdate(GuiInstance *gui, float dt);

void GuiSetColors(GuiInstance *gui, Color *colors);
Color GuiFetchColor(u8 state, u8 control);

bool Button(Rectangle rec, char *text, i8 icon);

#endif
