#include <stdio.h>
#include <string.h>
#include "config.h"

i8 ConfigRead(Config *conf, char *path) {
	FILE *pF = fopen(path, "r"); 	

	if(!pF) {
		printf("error: could not read config from file: %s\n", path);
		return 0;
	}

	char line[128];
	while(fgets(line, sizeof(line), pF)) 
		ConfigParseLine(conf, line);

	fclose(pF);

	return 1;
}

void ConfigParseLine(Config *conf, char *line) {
	if(line[0] == COMMENT_MARKER) return;

	char *eq = strchr(line, '=');
	if(!eq) return;

	*eq = '\0';
	char *key = line;
	char *val = eq + 1;

	if(streq(key, "window_width")) {
		return;
	}

	if(streq(key, "window_height")) {
		return;
	}
}

