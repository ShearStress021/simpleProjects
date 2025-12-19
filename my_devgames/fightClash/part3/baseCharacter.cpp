#include "baseCharacter.h"



BaseCharacter::BaseCharacter(){

}


Vector2 BaseCharacter::getWorldPosition(){
	return worldPosition;	

}

Rectangle BaseCharacter::getCollisionRec(){
	return {
		getCharacterPosition().x,
		getCharacterPosition().y,
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
	if (Vector2Length(velocity) != 0.0){
		worldPosition = Vector2Add(worldPosition, 
			Vector2Scale(Vector2Normalize(velocity),speed));
		velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
		texture = run;
	}else{
		texture = idle;
	}

	velocity = {};
	Rectangle source{frame * width, 0.f, rightLeft * width , height};
	Rectangle destination{getCharacterPosition().x, 
		getCharacterPosition().y,scale * width,scale * height};
	DrawTexturePro(texture, source,destination,Vector2{},0.f,WHITE);

}

BaseCharacter::~BaseCharacter(){}


