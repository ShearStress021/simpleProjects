#include "gameScene.hpp"


GameScene::GameScene(){
	tex.loadTexture("player", "data/sprites/gang/hero.png");
}

GameScene::~GameScene(){
}


Next GameScene::update(float deltaTime)  {
	return {};
}

void GameScene::render() const{
	BeginDrawing();
		const auto &player = tex.getTexture("player");
		DrawTexturePro(player,{0,0,(float)player.width,(float)player.height},{200,100,(float)player.width ,(float)player.height},{0},{},WHITE);
	EndDrawing();
}


