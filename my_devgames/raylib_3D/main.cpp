#include <iostream>
#include "raylib.h"
#include "renderer.hpp"

int main(void)
{

//#InitWindow(800, 450, "raylib example - basic window");
	if(!init_window(850, 450, "raylib 3d")){
		std::cerr << "Failed to Init Window\n";
		return 1;
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();

	}
	CloseWindow();
	return 0;
}
