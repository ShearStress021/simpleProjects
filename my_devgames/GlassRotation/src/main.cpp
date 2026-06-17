#include <raylib.h>
#include <iostream>
#include <raymath.h>

struct Glass {
	Rectangle bound{
		220.f,
		300.f,
		50.f,
		110.f
	};


	void draw(){
		DrawRectangleRoundedLines(bound, 0.3f, 8, Color{ 180,200,240,240 });

	}

	Vector2 RotateAround(Vector2 point, Vector2 pivot, float degrees){

		float radians = degrees * DEG2RAD;
		Vector2 relative = Vector2Subtract(point, pivot);
		relative = Vector2Rotate(relative, radians);
		return Vector2Add(pivot, relative);

	}

	void update(){
		Vector2 mouseHitPoint{GetMousePosition()};

		Vector2 point{bound.x, bound.y};
		Vector2 pivot{bound.x + bound.width/2, bound.y + bound.height/2};
		Vector2 result{};

		if (CheckCollisionPointRec(mouseHitPoint, bound)){
			if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
				result = RotateAround(point, pivot, 70);

			}


		}

		bound.x = result.x;
		bound.y = result.y;
	}


};



int main(void)
{
    InitWindow(1020, 720, "raylib example - basic window");


	Glass glass{};

	SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
			glass.draw();
			glass.update();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}



