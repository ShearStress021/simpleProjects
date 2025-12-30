#pragma  once
#include <glm/glm.hpp>
#include <vector>
#include "animation.h"



enum class ObjectType {
	player, level, enemy

};

struct GameObject{

	ObjectType type;
	glm::vec2 position, velocity, acceleration;
	float direction;


	GameObject(){
		type = ObjectType::level;
		direction = 1;
		position = velocity = acceleration = glm::vec2(0);


	}

};
