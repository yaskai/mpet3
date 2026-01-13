#include "ktypes.h"
#include "raylib.h"

#ifndef GUI_H_
#define GUI_H_

enum STYLE_COLOR_IDS {
	COLOR_BACKGROUND,
	COLOR_FOREGROUND,
	COLOR_BORDER,
	COLOR_TEXT
};

typedef struct {
	Color colors[4];
} GuiInstance;

void Button(Rectangle rec, char *text, i8 icon);

#endif
