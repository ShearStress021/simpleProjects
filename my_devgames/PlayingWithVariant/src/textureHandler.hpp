#pragma once
#include "helper.hpp"

#include <unordered_map>
#include <filesystem>
#include <string>



class TextureHandler {
	private:
		Texture fallback{};

		Texture& getFallbackTexture()
		{
			static Texture fallbackTexture;
			static bool loaded = false;

			if (!loaded) {
				Image image = GenImageChecked(8, 8, 2, 2, MAGENTA, BLACK);
				fallbackTexture = LoadTextureFromImage(image);
				UnloadImage(image);
				loaded = true;

			}
			return fallbackTexture;


		}

	public:

		TextureHandler(){
				Image image = GenImageChecked(8, 8, 2, 2, MAGENTA, BLACK);
				fallback = LoadTextureFromImage(image);
				UnloadImage(image);


		}
		Texture2D& loadTexture(const std::string &name, const std::string &path)
		{
			if (textures.count(name)) {
				return textures[name];

			}

			Texture texture = LoadTexture(path.c_str());
			if (texture.id == 0) {

				return fallback;

			}
			textures.insert({name, texture});
			return textures[name];


		}
		const Texture& getTexture(const std::string &name) const
		{
			if (!textures.count(name)) {
				return fallback;
			}
			return textures[name];


		}

};
