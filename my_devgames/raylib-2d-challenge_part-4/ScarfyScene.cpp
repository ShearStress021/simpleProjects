/** ScarfyScene.cpp
 *
 * See header file for details.
 */

#include "ScarfyScene.h"

ScarfyScene::ScarfyScene() {
}
	
ScarfyScene::~ScarfyScene() {
}
	
void ScarfyScene::loadResources() {
	std::shared_ptr<Scarfy> scarfy = std::make_shared<Scarfy>();
	
	int sceneWidth = GetScreenWidth();
	scarfy->position = raylib::Vector2(sceneWidth / 2, groundYPos);
	
	playerAvatar = scarfy;
	actors.emplace_back(scarfy);
}
