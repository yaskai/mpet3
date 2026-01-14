#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

i8 ConfigRead(Config *conf, char *path) {
	FILE *pF = fopen(path, "r"); 	

	if(!pF) return 0;

	i8 block = 0;
	char line[128];
	while(fgets(line, sizeof(line), pF)) { 
		ConfigParseLine(conf, line, &block);
	}

	fclose(pF);

	return 1;
}

void ConfigParseLine(Config *conf, char *line, i8 *block) {
	switch(line[0]) {
		// Skip parsing comments
		case COMMENT_MARKER: 
			return;

		case BLOCK_OPEN_MARKER:
			*block = ConfigParseLineBlock(conf, line); 
			return;
	}

	switch(*block) {
		case BLOCK_WINDOW:
			ConfigParseLineWindow(conf, line);
			break;

		case BLOCK_TEXT:
			ConfigParseLineText(conf, line);
			break;

		case BLOCK_COLORS:
			ConfigParseColor(conf, line, 0);
			break;

		case BLOCK_COLORS_HOVERED:
			ConfigParseColor(conf, line, 1);
			break;

		case BLOCK_COLORS_PRESSED:
			ConfigParseColor(conf, line, 2);
			break;
	}
}

i8 ConfigParseLineBlock(Config *conf, char *line) {
	char *open = line;
	char *close = strchr(line, BLOCK_CLOSE_MARKER);

	if(!close) return -1;
	*close = '\0';

	char *block_name = open + 1; 	

	if(streq(block_name, "window"))
		return BLOCK_WINDOW;
	else if (streq(block_name, "text"))
		return BLOCK_TEXT;
	else if (streq(block_name, "colors"))
		return BLOCK_COLORS;
	else if (streq(block_name, "colors_hovered"))
		return BLOCK_COLORS_HOVERED;
	else if (streq(block_name, "colors_pressed"))
		return BLOCK_COLORS_PRESSED;

	return -1;
}

void ConfigParseLineText(Config *conf, char *line) {
	char *eq = strchr(line, '=');
	if(!eq) return;
	
	*eq = '\0';
	char *key = line;
	char *val = eq + 1;

	if(streq(key, "size"))
		sscanf(val, "%d", &conf->font_size); 
	else if streq(key, "spacing")
		sscanf(val, "%d", &conf->font_spacing); 
}

void ConfigParseLineWindow(Config *conf, char *line) {
	char *eq = strchr(line, '=');
	if(!eq) return;

	*eq = '\0';
	char *key = line;
	char *val = eq + 1;

	// Window width
	if(streq(key, "window_width")) 
		sscanf(val, "%u", &conf->ww);

	// Window height
	if(streq(key, "window_height"))  
		sscanf(val, "%u", &conf->wh);
}

void ConfigParseColor(Config *conf, char *line, i8 state) {
	char *eq = strchr(line, '=');
	if(!eq) return;

	*eq = '\0';
	char *key = line;
	// Skip over open quote and '#' characters  
	char *val = eq + 3;

	// Remove closing quote character
	char *close = strchr(val, '"');	
	if(!close) return;
	*close = '\0';

	i32 hex;
	sscanf(val, "%x", &hex);

	// Convert hex values to RGB
	Color color = (Color) {
		.r = (hex >> 16),
		.g = (hex >>  8),
		.b = (hex >>  0),
		.a = 0xFF
	};

	// Get color index from key
	u8 id = COLOR_BACKGROUND + (COLOR_COUNT * state);
	if(streq(key, "background"))
		id += COLOR_BACKGROUND;
	else if(streq(key, "foreground"))
		id += COLOR_FOREGROUND;
	else if(streq(key, "border"))
		id += COLOR_BORDER;
	else if(streq(key, "text"))
		id += COLOR_TEXT;

	//printf("colors[%d] = %s\n", id, val);

	// Copy color to array at index 
	conf->colors[id] = color;
}

