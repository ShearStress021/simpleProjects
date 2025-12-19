
#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"
#include "baseCharacter.h"

class Character : public BaseCharacter{
	public:
		Character(int winWidth, int winHeight);
		virtual void tick(float deltaTime) override;
		Vector2 getCharacterPosition() override;
		float getHealth() const{return health;}
		void takeDamage(float damage);
		Rectangle getWeaponCollionRec(){return weaponCollisionRec;}
		~Character();
	private:
		int windowWidth{};
		int windowHeight{};
		Texture2D weapon{LoadTexture("../characters/weapon_sword.png")};
		Rectangle weaponCollisionRec{};
		float health{100.f};

};


#endif
