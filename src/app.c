#include <stdio.h>
#include "raylib.h"
#include "app.h"

void AppInit(App *app) {
	app->conf = (Config) {0};
	app->gui = (GuiInstance) {0};

	if(!ConfigRead(&app->conf, "options.conf")) 
		printf("ERROR: Could not read from configuration file\n");

	GuiInit(&app->gui, app->conf.colors);
}

void AppUpate(App *app, float dt) {
	/*
	for(u8 i = 0; i < COLOR_COUNT; i++) {
		DrawRectangle(i * (64 + 10), 64, 64, 64, app->conf.colors[i]);
		DrawRectangle(i * (64 + 10), 64 * 2, 64, 64, app->conf.colors[i + (COLOR_COUNT)]);
		DrawRectangle(i * (64 + 10), 64 * 3, 64, 64, app->conf.colors[i + (COLOR_COUNT * 2)]);
	}
	*/

	/*
	for(u8 i = 0; i < COLOR_COUNT; i++) {
		DrawRectangle(i * (64 + 10), 64, 64, 64, app->conf.colors[i]);
		DrawRectangle(i * (64 + 10), 64 * 2, 64, 64, app->conf.colors[i + (COLOR_COUNT)]);
		DrawRectangle(i * (64 + 10), 64 * 3, 64, 64, app->conf.colors[i + (COLOR_COUNT * 2)]);
	}
	*/
	
	GuiUpdate(&app->gui, dt);
	Button((Rectangle) { 300, 300, 256, 128 }, "This is a button", 0);
}

