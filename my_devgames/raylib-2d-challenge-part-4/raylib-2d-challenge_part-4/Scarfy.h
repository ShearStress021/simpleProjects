/** Scarfy.h
 *
 * @author Hans de Ruiter
 *
 * @copyright (c) 2022 by Kea Sigma Delta Limited, all rights reserved
 *
 * See License.txt for license.
 */

#pragma once

#include "Actor.h"

#include "raylib-cpp.hpp"

/** Our scarfy character.
 */
class Scarfy : public Actor {
public:
	/** Create Scarfy.
	 */
	Scarfy();
	
	virtual ~Scarfy();
	
	virtual bool update(bool onGround);
	
	virtual void draw();
	
	virtual raylib::Rectangle getBoundingBox();
	
	virtual void goUp();
	
	virtual void goLeft();
	
	virtual void goRight();
	
	virtual void goDown();
	
	virtual void goNowhere();
	
	/** Select, push, pull, punch, fire, etc.
	 */
	virtual void doInteractWith();
	
private:
	/** Calculates the position of this object's upper-left corner.
	 */
	raylib::Vector2 getUpperLeftPosition();

	raylib::Texture2D texture;
	
	raylib::Sound footstepSound;
	raylib::Sound landingSound;
	
	// Animation state
	unsigned numFrames;
	int frameWidth;
	unsigned frameDelay;
	unsigned frameDelayCounter;
	unsigned frameIndex;
	raylib::Rectangle frameRect;
	
	float jumpSpeed;
	float walkSpeed;
	
	bool isOnGround;
};