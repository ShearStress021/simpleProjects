#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H


#include "raylib.h"
#include "raymath.h"



class BaseCharacter{

	public:
		BaseCharacter();
		Vector2 getWorldPosition();
		void undoMovement();
		virtual void tick(float deltaTime);
		Rectangle getCollisionRec();
		virtual Vector2 getCharacterPosition() = 0;

		bool getAlive() {return alive;}
		void setAlive(bool isAlive) {alive = isAlive;}
		~BaseCharacter();
	protected:
		Texture2D texture{LoadTexture("../characters/goblin_idle_spritesheet.png")};
		Texture2D run{LoadTexture("../characters/knight_run_spritesheet.png")};
		Texture2D idle{LoadTexture("../characters/knight_idle_spritesheet.png")}; 
		Vector2 characterPosition{};
		Vector2 worldPosition{};
		Vector2 worldPositionBound{};
		const int maxFrames{6};
		int frame{};
		float runningTime{};
		float updateTime{1.f/12.0f};
		float rightLeft{-1.f};
		float speed{4.f};
		float width{};
		float height{};
		float scale{4.0f};

		Vector2 velocity{};
	private:
		bool alive{true};

};

#endif
