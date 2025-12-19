#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <iostream>
#include <ostream>
#include <string_view>
#include <string>
using namespace std;

int main(){
	const int windowHeight{384};
	const int windowWidth{384};

	InitWindow(windowWidth, windowHeight,"fight clash");



	// map background
	Texture2D map = LoadTexture("../nature_tileset/mymap.png");

	Vector2 mapPosition{};
	const float mapScale{4.0f};


	Character knight{windowWidth, windowHeight};




	Prop props[2]{
		Prop{LoadTexture("../nature_tileset/Rock.png"),Vector2{600.f,300.f}},
		Prop{LoadTexture("../nature_tileset/Log.png"), Vector2{400.f,500.f}}
	};





	Enemy goblin{Vector2{333.f, 500.f},
			LoadTexture("../characters/goblin_idle_spritesheet.png"),
			LoadTexture("../characters/goblin_run_spritesheet.png")};
	Enemy slime{Vector2{800.f, 800.f},
			LoadTexture("../characters/slime_idle_spritesheet.png"),
			LoadTexture("../characters/sli_run_spritesheet.png")};


	Enemy * enemies[]{
		&goblin,
		&slime
	};

	for (auto& enemy: enemies){
		enemy->setTarget(&knight);
	}


	SetTargetFPS(60); while(!WindowShouldClose()){ BeginDrawing(); ClearBackground(WHITE);

		// background map	
		//

		mapPosition = Vector2Scale(knight.getWorldPosition(),-1.f);
		
		DrawTextureEx(map,mapPosition,0.0,mapScale,WHITE);

		

		for(auto& prop : props){
			prop.render(knight.getWorldPosition());

			

		}
		if (!knight.getAlive()){
			DrawText("Game Over", 55.f, 45.f, 40, RED);
			EndDrawing();
			continue;

		}
		else {
			string damageStr = "Health: ";
			damageStr.append(to_string(knight.getHealth()),0,5);
			DrawText(damageStr.c_str(), 55.f, 45.f, 40, GREEN);

		}
		
		knight.tick(GetFrameTime());

		// Check map undo
		if (knight.getWorldPosition().x < 0.f ||
				knight.getWorldPosition().y < 0.f ||
				knight.getWorldPosition().x + windowWidth > map.width * mapScale||
				knight.getWorldPosition().y + windowWidth > map.height * mapScale){
			knight.undoMovement();
			
		}
		
		for (auto& prop : props){
			if (CheckCollisionRecs(knight.getCollisionRec(), 
						prop.getCollisionRec(knight.getWorldPosition()))){
				knight.undoMovement();
			}
		}

		for (auto & enemy: enemies){
			
			enemy->tick(GetFrameTime());

		}


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
			for(auto & enemy: enemies){
				if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollionRec())){
					enemy->setAlive(false);
			}


			}
		}
		
		EndDrawing();
	}
	CloseWindow();
}
