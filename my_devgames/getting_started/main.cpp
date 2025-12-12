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
	int u_r_y{r_y};
	int b_r_y{r_y + r_l};


	int upDown{10};
	int leftRight{10};


	bool collision = (b_r_y >= u_circle_y) && 
					(u_r_y <= b_circle_y) && 
					(r_r_x >= l_circle_x) &&
					(l_r_x <= r_circle_x);

	
	SetTargetFPS(60);
	while(WindowShouldClose() == false){
		BeginDrawing();
		ClearBackground(WHITE);

		if (collision){
			DrawText("Game Over",400,200,25,RED);
		}else {

			// Game Logic begin
			//
			// Update edges
			l_circle_x = c_x - c_r;
			r_circle_x = c_x + c_r;
			u_circle_y = c_y - c_r;
			b_circle_y = c_y + c_r;
			

			l_r_x = r_x;
			r_r_x = r_x + r_l;
			u_r_y = r_y;
			b_r_y = r_y + r_l;

			DrawCircle(c_x, c_y,c_r, BLUE);
			DrawRectangle(r_x, r_y, r_l,r_l,RED);


			
		 	collision = (b_r_y >= u_circle_y) && 
							(u_r_y <= b_circle_y) && 
							(r_r_x >= l_circle_x) &&
							(l_r_x <= r_circle_x);





			// Moving


			r_y += upDown;
			if (r_y > height || r_y < 0){
				upDown=  -upDown;

			}
			if (IsKeyPressed(KEY_D) && c_x <= width){
				c_x += leftRight;
			}

			if(IsKeyDown(KEY_A) && c_x >= 0){
				c_x -= leftRight;
			}


		}
		
		// Game Logic end
		EndDrawing();


	}
	
}
