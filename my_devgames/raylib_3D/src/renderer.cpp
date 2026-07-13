#include "raylib.h"
#include "renderer.hpp"

#define MAX_TEX 256


static Texture2D getTex[MAX_TEX];
static int texCount{0};

bool init_window(int width, int height, const std::string_view title){

	InitWindow(width, height, title.data());
	if(!IsWindowReady()) return false;
	return true;
}



bool windowShouldClose(void){return WindowShouldClose();}


texture loadTextureRGBA(const uint8_t *rgba, int w, int h){
	if(texCount > MAX_TEX) return -1;

	Image image = {
		.data = (void *)rgba,
		.width = w, .height =h, .mipmaps =1,
		.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
	};

	Texture2D t = LoadTextureFromImage(image);
	SetTextureFilter(t, TEXTURE_FILTER_BILINEAR);
	getTex[texCount] = t;
	return texCount++;
}

texture loadTextureFile(const std::string_view path){
	if (texCount >= MAX_TEX) return -1;

	Texture2D t = LoadTexture(path.data());
	if(t.id == 0) return -1;
	SetTextureFilter(t, TEXTURE_FILTER_BILINEAR);
	getTex[texCount] = t;
	return texCount ++;
}





