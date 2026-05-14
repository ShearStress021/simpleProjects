#include <raylib.h>


int main(){

	InitWindow(920, 720, "raylib example - basic window");

//	SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
			DrawCircle(60.f,60.f,20.f,RED);
        EndDrawing();
    }

    CloseWindow();
	return 0;
}
