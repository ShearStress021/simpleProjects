#include "raylib.h"
#include "raymath.h"



int main(){
	

	const int windowHeight{384};
	const int windowWidth{384};

	InitWindow(windowWidth, windowHeight,"fight clash");



	// map background
	Texture2D map = LoadTexture("../nature_tileset/mymap.png");

	Vector2 mapPosition{};
	const float mapScale{4.0f};
	const float speed{4.0};



	Texture2D knight = LoadTexture("../characters/knight_idle_spritesheet.png");
	Vector2 knightPosition{
			(float)windowWidth/2.0f - 4.0f *(0.5f * knight.width/6),
		(float)windowHeight/2.0f - 4.0f * (0.5f * knight.height )

	};

	float rightLeft{-1.f};

	float runningTime{};
	const float updateTime{1.0/12.0f};
	int frame{};
	const int maxFrames{6};
	

	Texture2D knightIdle = LoadTexture("../characters/knight_idle_spritesheet.png");
	Texture2D knightRun = LoadTexture("../characters/knight_run_spritesheet.png");
	


	SetTargetFPS(60);
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(WHITE);

		Vector2 direction{};
		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;


		if (Vector2Length(direction) != 0.0){
			mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction),speed));

			direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
			knight = knightRun;
		}else{
			knight = knightIdle;
		}

		// background map	


		DrawTextureEx(map,mapPosition,0.0,mapScale,WHITE);

		runningTime += GetFrameTime();
		if (runningTime >= updateTime){
			frame ++;
			runningTime = 0.f;
			if (frame > maxFrames) frame = 0;
		}

		Rectangle source{frame*(float)knight.width/6.0f,0.f,rightLeft * (float)knight.width/6.f , (float)knight.height};
		Rectangle destination{knightPosition.x, knightPosition.y,4.f * knight.width/6.f,4.f * (float)knight.height};

		DrawTexturePro(knight, source,destination,Vector2{},0.f,WHITE);


		EndDrawing();

	}
	CloseWindow();
}
