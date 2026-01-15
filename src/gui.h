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
	RenderTexture2D render_target;

	char **text;
	
	Vector2 position;
	Vector2 entry_size;

	float scroll;
	float visual_scroll;
	float offset;
	float scroll_vel;
	
	u16 count;
	u16 display_count; 

	i8 scroll_dir;
	
} ButtonList;

typedef struct {
	Font font;

	Color colors[COLOR_COUNT * 3];

	Vector2 cursor_position;

	u32 font_size;
	u32 font_spacing;

} GuiInstance;

void GuiInit(GuiInstance *gui, Config *conf);
void GuiUpdate(GuiInstance *gui, float dt);

void GuiSetColors(Color *colors);
Color GuiFetchColor(u8 state, u8 control);

Vector2 TextCenter(Rectangle rec, char *text);
Vector2 TextCenterEx(Rectangle rec, char *text, float font_size, float font_spacing);

bool Button(Rectangle rec, char *text, i8 icon);
bool ButtonEx(Rectangle rec, char *text, i8 icon, float font_size, float font_spacing, float alpha);

void UpdateButtonList(ButtonList *button_list, float dt);
void TestUpdateButtonList(float dt);

#endif
