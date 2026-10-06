#pragma once
#include "helper.hpp"
#include "textureHandler.hpp"


class StartScene{

	public: 
		StartScene();
		~StartScene();
		void render() const;
		Next update(float deltaTime);
	private:
		TextureHandler tex{};

		float timer{};
		
};
