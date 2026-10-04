#include "startScene.hpp"


StartScene::StartScene (){
	tex.loadTexture("loader", "data/sprites/loading.png");
}


StartScene::~StartScene(){
}

void StartScene::render() const{
	BeginDrawing();
		const auto &loader = tex.getTexture("loader");
		DrawTexturePro(loader,{0,0,loader.width/1.f,loader.height/1.f}, {GetScreenWidth()/2.f, GetScreenHeight()/2.f, 
				(float)loader.width * 2, (float)loader.height * 2},
				{float(loader.width), (float)loader.height}, {}, WHITE);

	EndDrawing();
}

Next StartScene::update(float deltaTime){
	timer += deltaTime;
	if(timer > 2.0f) return SceneId::Game;
	return {};
}


