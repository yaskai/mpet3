#include "ktypes.h"
#include "raylib.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define COMMENT_MARKER 		'#'
#define BLOCK_OPEN_MARKER 	'['
#define BLOCK_CLOSE_MARKER 	']'

#define streq(a, b) (!strcmp(a, b))

enum CONFIG_BLOCKS : u8 {
	BLOCK_WINDOW,	
	BLOCK_TEXT,
	BLOCK_COLORS,
	BLOCK_COLORS_HOVERED,
	BLOCK_COLORS_PRESSED
};

#define COLOR_COUNT 4
enum UI_COLORS : u8 { 
	COLOR_BACKGROUND,
	COLOR_FOREGROUND,
	COLOR_BORDER,
	COLOR_TEXT
};

typedef struct {

} OptionEntry;

typedef struct {
	Color colors[12];

	unsigned int ww; 
	unsigned int wh;

	u32 font_size;
	u32 font_spacing;

	u16 fps;
	u8 flags;

} Config;

i8 ConfigRead(Config *conf, char *path);

void ConfigParseLine(Config *conf, char *line, i8 *block);

i8 ConfigParseLineBlock(Config *conf, char *line);

void ConfigParseLineText(Config *conf, char *line);

void ConfigParseLineWindow(Config *conf, char *line);

void ConfigParseColor(Config *conf, char *line, i8 state);

Color ParseColor(char *line);
Color HexToRgb(unsigned int hex);

#endif
