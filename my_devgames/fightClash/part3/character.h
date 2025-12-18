
#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"
#include "baseCharacter.h"

class Character : public BaseCharacter{
	public:
		Character(int winWidth, int winHeight);
		virtual void tick(float deltaTime) override;
		Vector2 getCharacterPosition(){return characterPosition;}
		~Character();
	private:

};


#endif
