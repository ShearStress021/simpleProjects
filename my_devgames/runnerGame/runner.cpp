#include "raylib.h"



int main(){



	// window dimensions
	const int windowWidth = 512;
	const int windowHeight = 380;
	

	// Initialize window
	InitWindow(windowWidth, windowHeight, "City Runner");

	// gravity
	const int gravity{1};


	// using Texture2D
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	Rectangle scarfyRec;
	scarfyRec.height = scarfy.height;
	scarfyRec.width = scarfy.width/6;
	scarfyRec.x = 0;
	scarfyRec.y = 0;
	Vector2 scarfyPos;

	scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
	scarfyPos.y = windowHeight - scarfy.height;




	bool isInAir{};


	int velocity{0};

	const int jumpDistance{-10};



	

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		//  Start drawing
		BeginDrawing();
		ClearBackground(WHITE);


		if(scarfyPos.y >= windowHeight - scarfyRec.height){
			// Rectangle is on ground
			velocity = 0;
			isInAir = false;
		} else {
			velocity += gravity;
			isInAir = true;
		}


		if (IsKeyPressed(KEY_SPACE) && !isInAir){
			velocity = jumpDistance;

		}
		
		scarfyPos.y += velocity;

		DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);
		


		// stop drawing
		EndDrawing();

	}

	UnloadTexture(scarfy);
	CloseWindow();

}
