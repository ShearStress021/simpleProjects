#include <iostream>
#include "prop.h"

Prop::Prop(Texture2D tex, Vector2 pos) :
	texture(tex),
	worldPosition(pos)
{
	
}


void Prop::render(Vector2 knightPos){
	Vector2 screenPos{Vector2Subtract(worldPosition, knightPos)} ;


	DrawTextureEx(texture, screenPos,0.f,scale,WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos){
	Vector2 screenPos{Vector2Subtract(worldPosition, knightPos)} ;
	return Rectangle {
		screenPos.x,
			screenPos.y,
			texture.width * scale,
			texture.height * scale
	};

}
Prop::~Prop(){}
