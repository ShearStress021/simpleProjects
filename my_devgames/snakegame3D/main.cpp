#include <iostream>
#include "raylib.h"





namespace Settings {
	constexpr std::size_t GRID_SIZE{10};
	constexpr float CUBE_SIZE{0.5f};
	constexpr float CUBE_SPACING{.25f};
	constexpr float TICK_SECONDS{.3f};
}


using GridPos = std::array<int, 3>;

enum class Axis {
	X=0,Y=1,Z=2
};

Camera3D createCamera(){
	Camera3D camera{};
	camera.position = {10, 10, 10};
	camera.fovy = 60;
	camera.up = {0, 1, 0};
	camera.projection = CAMERA_PERSPECTIVE;
	return camera;
}

class Game{
	public:
		void update(float dt){
			m_counter += dt;
			if(m_counter > Settings::TICK_SECONDS){
				makeTick();
				m_counter = 0;
			}
		}

	private:
		void makeTick(){
			std::cout << "Made tick" <<'\n';

		}

	private:
		float m_counter{};

};


int main(){
	InitWindow(800, 450, "raylib example - basic window");
	auto camera{createCamera()};

	Game game{};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		game.update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode3D(camera);

		DrawCube({},1,2,1,YELLOW);
		EndMode3D();
		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
