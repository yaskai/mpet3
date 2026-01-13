#include "raylib.h"
#include "app.h"

int main() {
	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);
	InitWindow(1280, 800, "Raylib Project");

	while(!WindowShouldClose()) {
		float delta_time = GetFrameTime();

		BeginDrawing();
		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

