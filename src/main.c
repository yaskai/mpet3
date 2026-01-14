#include <stdio.h>
#include "raylib.h"
#include "app.h"

int main() {
	SetTraceLogLevel(LOG_ERROR);

	App app = (App) {0};
	if(!ConfigRead(&app.conf, "options.conf")) 
		printf("ERROR: Could not read from configuration file\n");

	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);
	InitWindow(app.conf.ww, app.conf.wh, "mpet3");

	AppInit(&app);

	while(!WindowShouldClose()) {
		float delta_time = GetFrameTime();

		BeginDrawing();
		ClearBackground(BLACK);

		AppUpate(&app, delta_time);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

