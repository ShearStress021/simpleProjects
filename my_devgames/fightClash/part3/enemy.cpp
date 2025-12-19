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
	
	// Normalize To Target
	// Multiply toTarget by speed
	//
	if (!getAlive()) return;
	// Move the Enemy
	velocity = Vector2Subtract(target->getCharacterPosition(), getCharacterPosition());
	if (Vector2Length(velocity) < radius) velocity = {};
	
	characterPosition = Vector2Subtract(worldPosition, target->getWorldPosition());
	
	BaseCharacter::tick(deltaTime);


	if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())){
		target->takeDamage(damagePerSec* deltaTime);
	}


}

Vector2 Enemy::getCharacterPosition(){
	return Vector2Subtract(worldPosition, target->getWorldPosition());
}

Enemy::~Enemy(){}
