#include <stdio.h>
#include "raylib.h"
#include "app.h"

void AppInit(App *app) {
	app->gui = (GuiInstance) {0};


	GuiInit(&app->gui, &app->conf);
}

void AppUpate(App *app, float dt) {
	GuiUpdate(&app->gui, dt);
	Button((Rectangle) { 300, 300, 356, 128 }, "This is a button", 0);
}

