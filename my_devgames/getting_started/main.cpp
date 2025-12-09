#include "raylib.h"

int main(){;

	// Window dimensions
	int width{800};
	int height{450};
	InitWindow(width, height,"anjaks");
	


	// Circle Coordinates
	int c_x = 175;
	int c_y = 100;
	int c_r = 25;

	// circle edges
	int l_circle_x{c_x - c_r};
	int r_circle_x{c_x + c_r};
	int u_circle_y{c_y - c_r};
	int b_circle_y{c_y + c_r};

	int r_x = 400;
	int r_y = 0;
	int r_l = 50;

	int l_r_x {r_x};
	int r_r_x{r_x + r_l};
	int u_r_x{r_y};
	int b_r_x{r_y + r_l};


	int direction{10};


	bool collision{true};

	


	
	SetTargetFPS(60);
	while(WindowShouldClose() == false){
		BeginDrawing();
		ClearBackground(WHITE);


		if (collision){
			DrawText("Game Over",400,200,25,RED);
		}else {

			// Game Logic begin

			DrawCircle(c_x, c_y,c_r, BLUE);
			DrawRectangle(r_x, r_y, r_l,r_l,RED);






			// Moving


			r_y += direction;
			if (r_y > height || r_y < 0){
				direction  =  -direction;

			}
			if (IsKeyDown(KEY_D) && c_x <= width){
				c_x += direction;
			}

			if(IsKeyDown(KEY_A) && c_x >= 0){
				c_x -= 10;
			}


		}
		
		// Game Logic end
		EndDrawing();


	}
	
}
