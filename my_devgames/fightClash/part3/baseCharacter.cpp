#include "baseCharacter.h"


BaseCharacter::BaseCharacter(){

}


Vector2 BaseCharacter::getWorldPosition(){
	return worldPosition;	

}

Rectangle BaseCharacter::getCollisionRec(){
	return {
		characterPosition.x,
		characterPosition.y,
		width * scale,
		height * scale
	};
}
void BaseCharacter::undoMovement(){
	worldPosition = worldPositionBound;
}

void BaseCharacter::tick(float deltaTime) {
	worldPositionBound = worldPosition;

	runningTime += deltaTime;
	if (runningTime >= updateTime){
		frame ++;
		runningTime = 0.f;
		if (frame > maxFrames) frame = 0;
	}
	Rectangle source{frame * width, 0.f, rightLeft * width , height};
	Rectangle destination{characterPosition.x, 
		characterPosition.y,scale * width,scale * height};
	DrawTexturePro(texture, source,destination,Vector2{},0.f,WHITE);

}

BaseCharacter::~BaseCharacter(){}


