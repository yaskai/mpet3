#include <stdio.h>
#include "raylib.h"
#include "app.h"

void AppInit(App *app) {
	app->gui = (GuiInstance) {0};

	GuiInit(&app->gui, &app->conf);
}

void AppUpate(App *app, float dt) {
	TestUpdateButtonList(dt);

	BeginDrawing();
	ClearBackground(BLACK);

	GuiUpdate(&app->gui, dt);

	EndDrawing();
}

