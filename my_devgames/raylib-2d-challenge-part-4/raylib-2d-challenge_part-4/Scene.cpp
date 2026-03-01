/** Scene.cpp
 *
 * See header file for details.
 */

#include "Scene.h"

#include "Actor.h"
#include "MainMenuScene.h"
#include "raylib.h"

Scene::Scene() {
	int sceneHeight = GetScreenHeight();
	groundYPos = (3 * sceneHeight) / 4;
	gravity = 1;
	exit = false;
}
	
Scene::~Scene() {
	freeResources();
}
	
void Scene::loadResources() {
}
	
void Scene::freeResources() {
	playerAvatar.reset();
	actors.clear();
}
	
void Scene::start() {
}
	
std::shared_ptr<Scene> Scene::update() {
	for(auto &actor : actors) {
		actor->position += actor->velocity;
		
		auto boundingRect = actor->getBoundingBox();
		auto distToGround = groundYPos - (boundingRect.y + boundingRect.height);
		bool isOnGround =  distToGround <= 0;
		
		if(isOnGround) {
			actor->velocity.y = 0;
			actor->position.y += distToGround;
		} else {
			actor->velocity.y += gravity;
		}
		actor->update(isOnGround);
	}
	
	if(exit) {
		exit = false;
		return std::make_shared<MainMenuScene>();
	} else {
		return nullptr;
	}
}

bool Scene::shouldQuit() {
	return false;
}
	
void Scene::draw() {
	ClearBackground(RAYWHITE);
		
	if(actors.size()) {
		for(auto &actor: actors) {
			actor->draw();
		}
	}
}
	
void Scene::goUp() {
	if(playerAvatar) {
		playerAvatar->goUp();
	}
}
	
void Scene::goLeft() {
	if(playerAvatar) {
		playerAvatar->goLeft();
	}
}
	
void Scene::goRight() {
	if(playerAvatar) {
		playerAvatar->goRight();
	}
}
	
void Scene::goDown() {
	if(playerAvatar) {
		playerAvatar->goDown();
	}
}

void Scene::goNowhere() {
	if(playerAvatar) {
		playerAvatar->goNowhere();
	}
}
	
void Scene::doInteractWith() {
	if(playerAvatar) {
		playerAvatar->doInteractWith();
	}
}

void Scene::doExit() {
	exit = true;
}