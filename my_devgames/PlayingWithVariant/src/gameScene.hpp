#pragma once
#include "helper.hpp"
#include "textureHandler.hpp"


class GameScene {
	public:
		GameScene();
		~GameScene();
		Next update(float deltaTime);
		void render() const;



	private:
		TextureHandler tex{};
};
