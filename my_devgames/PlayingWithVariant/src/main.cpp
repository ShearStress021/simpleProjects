#include <raylib.h>
#include "scenes.hpp"
#define WIDTH 1024
#define HEIGHT 768 


int main()
{
	InitWindow(WIDTH, HEIGHT, "raylib example - basic window");
	Scene scene{};
	switchTo(scene, SceneId::Start);


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		const Next next = updateScene(scene, GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		renderScene(scene);

		
		EndDrawing();

		if(next){
			if(*next == SceneId::Quit) break;
			switchTo(scene,*next);
		}

	}

	CloseWindow();

	return 0;

}
