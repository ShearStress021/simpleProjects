#include "character.h" 
#include <iostream>


Character::Character(int winWidth, int winHeight):
	windowWidth(winWidth),
	windowHeight(winHeight)


{
	
	width = texture.width / maxFrames;
	height = texture.height ;
}

void Character::tick(float deltaTime) {


		
		if (!getAlive()) return;
		if (IsKeyDown(KEY_A)) velocity.x -= 1.0;

		if (IsKeyDown(KEY_D)) velocity.x += 1.0;
		if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
		if (IsKeyDown(KEY_S)) velocity.y += 1.0;
		BaseCharacter::tick(deltaTime);


		Vector2 origin{};
		Vector2 offSet{};
		float rotation{};

		if (rightLeft > 0.f){
			origin = {0.f, weapon.height * scale};
			offSet = {35.f, 55.f};

			weaponCollisionRec = {
				getCharacterPosition().x + offSet.x,
					getCharacterPosition().y + offSet.y - weapon.height * scale,
					weapon.width * scale,
					weapon.height * scale

			};

			rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;

		}
		else {
			origin = {weapon.width * scale, weapon.height * scale};
			offSet = {25.f, 55.f};
			weaponCollisionRec = {
				getCharacterPosition().x + offSet.x - weapon.width * scale,
					getCharacterPosition().y + offSet.y - weapon.height * scale,
					weapon.width * scale,
					weapon.height * scale

			};
			rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
		}


		Rectangle source{0.f,0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
		Rectangle destination{getCharacterPosition().x + offSet.x, getCharacterPosition().y + offSet.y, 
			static_cast<float>(weapon.width) * 4,static_cast<float>(weapon.height) * scale};
		DrawTexturePro(weapon, source,destination, origin, rotation, WHITE);


}

Vector2 Character::getCharacterPosition(){
	return Vector2{
			static_cast<float>(windowWidth)/2.0f - scale *(0.5f * width),
			static_cast<float>(windowHeight)/2.0f - scale * (0.5f * height )
	};
}

void Character::takeDamage(float damage){
	health -= damage;
	if (health <= 0.f){
		setAlive(false);
	}
}

Character::~Character(){}
