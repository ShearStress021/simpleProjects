#include "raylib.h"
#include "raymath.h"

class Prop{

	public:
		Prop(Texture2D tex, Vector2 pos);
		void render(Vector2 knightPos);
		Rectangle getCollisionRec(Vector2 knightPos);
		~Prop();
	private:
		Texture2D texture{};
		Vector2 worldPosition{};
		float scale{4.f};

};
