/** Actor.cpp
 *
 * See the header file for details.
 */

#include "Actor.h"

#include "Functions.hpp"
#include "Text.hpp"

Actor::Actor() {
}
	
Actor::~Actor() {
}

bool Actor::update(bool onGround) {
	return true;
}

void Actor::draw() {
	raylib::Text message("Override Actor::draw()", 20, RED, ::GetFontDefault(), 1.0f);
	auto textSize = message.MeasureEx();
	message.Draw(position, 0, textSize / 2);
}

raylib::Rectangle Actor::getBoundingBox() {
	return raylib::Rectangle(position.x, position.y);
}
