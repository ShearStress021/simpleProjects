#include "raylib.h"
#include <iostream>
using namespace std;


struct AnimationData{
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;

};


bool isOnGround(AnimationData data, float windowHeight){
	return data.pos.y >= windowHeight - data.rec.height;
}


AnimationData updateAnimationData (AnimationData data, float deltaTime, int maxFrame){
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime){
		data.runningTime = 0;
		data.rec.x = data.frame * data.rec.width;
		data.frame ++;
		if (data.frame > maxFrame){
			data.frame = 0;
		}
	}
	return data;
}

int main(){


	float windowDimensions[2];
	windowDimensions[0] = 512;
	windowDimensions[1] = 380;

	// window dimensions

	// Initialize window
	InitWindow(windowDimensions[0], windowDimensions[1], "City Runner");

	// gravity
	const int gravity{1000};




	// Nebula section
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	const int sizeOfNebula{3};

	AnimationData nebulaData[sizeOfNebula]{};


	for (int i = 0; i < sizeOfNebula; i++){
		nebulaData[i].rec.x = 0.0;
		nebulaData[i].rec.y = 0.0;
		nebulaData[i].rec.width = nebula.width /8;
		nebulaData[i].rec.height = nebula.height /8;
		nebulaData[i].pos.x = windowDimensions[0] + i * 300;
		nebulaData[i].pos.y = windowDimensions[1]  - nebula.height / 8;
		nebulaData[i].frame = 0;
		nebulaData[i].runningTime = 0;
		nebulaData[i].updateTime = 1.0/16.0;


	}


	float finishLine{nebulaData[sizeOfNebula-1].pos.x};


	// Scarfy variables Texture2D scarfy = LoadTexture("textures/scarfy.png");
	//
    
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
    // Lines 51-58 (Initialization must follow declaration)
	float heightPos = scarfy.height;
    AnimationData scarfyData {
        // Here, scarfy is now properly declared
        {0.0f, 0.0f, scarfy.width / 6.0f, heightPos},
        {windowDimensions[0]/ 2.0f - (scarfy.width/6.0f)/2.0f , windowDimensions[1]- heightPos},
        0,                    
        1.0/12.0,
        0.0                    
    };
	bool isInAir{};



	int velocity{0};

	// pixel second
	const int jumpDistance{-600};

	int nebulaVelocity{-200};


	Texture2D background = LoadTexture("textures/far-buildings.png");


	float bgX{};

	Texture2D midground = LoadTexture("textures/back-buildings.png");

	float midgroundX{};

	Texture2D foreground = LoadTexture("textures/foreground.png");

	float foregroundX{};




		

	bool collision{};
	

	SetTargetFPS(60);
	while(!WindowShouldClose()){

		// delta time
		const float deltaTime{GetFrameTime()};

//		std:cout<< "%d" << deltaTime <<"\n";

		//  Start drawing
		BeginDrawing();
		ClearBackground(WHITE);



		bgX -= 20 * deltaTime;


		midgroundX -= 40 * deltaTime;

		if (bgX <= - background.width * 2){
			bgX = 0;
		}

		if (midgroundX <= -midground.width * 2){
			midgroundX = 0;
		}

		


		// Draw background
		Vector2 background1Position{bgX,0.0};

		DrawTextureEx(background, background1Position,0.0,2.0,WHITE);


		Vector2 background2Position{bgX + background.width * 2,0.0};
		DrawTextureEx(background, background2Position, 0.0,2.0,WHITE);

		Vector2 midground1Position{midgroundX,0.0} ;
		DrawTextureEx(midground,midground1Position,0.0,2.0,WHITE);
//		DrawTexture
		Vector2 midground2Position{midgroundX + midground.width * 2,0.0} ;
		DrawTextureEx(midground, midground2Position, 0.0, 2.0,WHITE);


		foregroundX -=  80 * deltaTime;

		if (foregroundX <= -foreground.width * 2){
			foregroundX = 0;
		}

		
		Vector2 foreground1Position{foregroundX,0.0};
		
		DrawTextureEx(foreground,foreground1Position,0.0,2.0,WHITE);
		
		

		Vector2 foreground2Position{foregroundX+foreground.width * 2,0.0};
		
		DrawTextureEx(foreground,foreground2Position,0.0,2.0,WHITE);
		
	


		if(isOnGround(scarfyData, windowDimensions[1])){
			// Rectangle is on ground
			velocity = 0;
			isInAir = false;
		} else {

			velocity += gravity * deltaTime;
			isInAir = true;
		}


		if (IsKeyPressed(KEY_SPACE) && !isInAir){
			velocity += jumpDistance;

		}
		

		for(AnimationData nebula: nebulaData){

			float pad{50};
			Rectangle nebRec{nebula.pos.x + pad, 
							nebula.pos.y + pad,
							nebula.rec.width - 2*pad,
							nebula.rec.height - 2 * pad};

			Rectangle scarfyRec {
				scarfyData.pos.x ,
					scarfyData.pos.y,
					scarfyData.rec.width,
					scarfyData.rec.height
			};

			if (CheckCollisionRecs(nebRec, scarfyRec)){
				collision = true;
			}
		}
		//update nebula position
		for (int i = 0; i < sizeOfNebula; i ++){
			nebulaData[i].pos.x  += nebulaVelocity * deltaTime;
		}
		
		finishLine += nebulaVelocity * deltaTime;
		// update scafy position
		scarfyData.pos.y += velocity * deltaTime;
		


		// scarfy animation code
		if (!isInAir){

		// update running time
		scarfyData = updateAnimationData(scarfyData,deltaTime, 5) ;
		}




		// nebula animation code

		for (int i = 0; i < sizeOfNebula; i ++){
			nebulaData[i] = updateAnimationData(nebulaData[i], deltaTime, 7);
		}

		if (collision){
			DrawText("GameOver",windowDimensions[0]/4,windowDimensions[1]/2,40,RED);

		}
		else if(scarfyData.pos.x >= finishLine){

			DrawText("You Win",windowDimensions[0]/4,windowDimensions[1]/2,40,GREEN);

		}
		else {

			for(int i = 0; i < sizeOfNebula; i++){
				DrawTextureRec(nebula,nebulaData[i].rec,nebulaData[i].pos, WHITE);	

			}
			DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

		}


		// stop drawing
		EndDrawing();

	}


	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	UnloadTexture(background);
	UnloadTexture(midground);
	UnloadTexture(foreground);
	CloseWindow();
}

