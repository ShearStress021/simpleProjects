#pragma  once
#include <glm/glm.hpp>
#include <vector>
#include "animation.h"
#include <SDL3/SDL.h>


enum class PlayerState {
    idle, running, jumping
};


struct PlayerData {
    PlayerState state{};
	Timer weaponTimer;
    PlayerData(): weaponTimer(0.1f)
    {
        state =  PlayerState::idle;
    }
};

enum class ObjectType {
	player, level, enemy, bullet

};
enum class BulletState 
{
	moving, colling, inactive
};

struct LevelData 
{

};

struct EnemyData
{

};

struct BulletData 
{

	BulletState state;
	BulletData(): state(BulletState::moving)
	{

	}
};
union ObjectData
{
    PlayerData player;
	LevelData level;
	EnemyData enemy;
	BulletData bullet;

};
struct GameObject{

	ObjectType type{};
	ObjectData data{};
	glm::vec2 position, velocity, acceleration;
	float direction{};
	float maxSpeedx{};
	std::vector<Animation> animations;
	int currentAnimation;
	SDL_Texture *texture;
	bool dynamic{};
	bool grounded{}; SDL_FRect collider{};

	GameObject() : data{.level = LevelData()}, collider{0}
	{
		type = ObjectType::level;
		direction = 1;
		position = velocity = acceleration = glm::vec2(0);
		currentAnimation = -1;
		texture = nullptr;
		maxSpeedx = 0;
		dynamic = false;
		grounded = false;
	}

};
