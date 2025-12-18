#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <iostream>
#include <ostream>
#include <string_view>

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


	Enemy goblin{Vector2{},
			LoadTexture("../characters/goblin_idle_spritesheet.png"),
			LoadTexture("../characters/goblin_run_spritesheet.png")};

	goblin.setTarget(&knight);


	SetTargetFPS(60); while(!WindowShouldClose()){ BeginDrawing(); ClearBackground(WHITE);

		// background map	
		//

		mapPosition = Vector2Scale(knight.getWorldPosition(),-1.f);
		
		DrawTextureEx(map,mapPosition,0.0,mapScale,WHITE);

		

		for(auto& prop : props){
			prop.render(knight.getWorldPosition());

			

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

		goblin.tick(GetFrameTime());
		
		EndDrawing();
	}
	CloseWindow();
}
