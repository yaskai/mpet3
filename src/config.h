#include "ktypes.h"
#include "raylib.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define COMMENT_MARKER '#'
#define streq(a, b) (!strcmp(a, b))

enum UI_COLORS : u8 { BG, FG, HL, BGA };

typedef struct {

} OptionEntry;

typedef struct {
	Color colors[4];

	u16 ww; 
	u16 wh;
	u16 fps;

	u8 flags;

} Config;

i8 ConfigRead(Config *conf, char *path);
void ConfigParseLine(Config *conf, char *line);

Color ParseColor(char *line);
Color HexToRgb(unsigned int hex);

#endif
