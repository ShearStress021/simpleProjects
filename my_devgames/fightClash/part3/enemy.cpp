#include "enemy.h"




Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
	worldPosition = pos;
	texture = idle_texture;
	idle = idle_texture;
	run = run_texture;
	width = texture.width / maxFrames,
	height = texture.height;
	speed = 3.5f;

}


void Enemy::tick(float deltaTime ){
	// Get To Target Vector
	 Vector2 toTarget = Vector2Subtract(target->getCharacterPosition(), characterPosition);
	
	// Normalize To Target
	toTarget = Vector2Normalize(toTarget);
	// Multiply toTarget by speed
	toTarget = Vector2Scale(toTarget, speed);
	//
	// Move the Enemy
	worldPosition = Vector2Add(worldPosition, toTarget);
	characterPosition = Vector2Subtract(worldPosition, target->getWorldPosition());
	
	BaseCharacter::tick(deltaTime);


}

Enemy::~Enemy(){}
