#include "raylib.h"
#include "app.h"

int main() {
	SetTraceLogLevel(LOG_ERROR);

	App app = (App) {0};
	AppInit(&app);

	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);
	InitWindow(app.conf.ww, app.conf.wh, "Raylib Project");

	while(!WindowShouldClose()) {
		float delta_time = GetFrameTime();

		BeginDrawing();
		ClearBackground(BLUE);

		AppUpate(&app, delta_time);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

