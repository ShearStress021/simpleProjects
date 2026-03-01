/** Scene.h
 *
 * @author Hans de Ruiter
 *
 * @copyright (c) 2022 by Kea Sigma Delta Limited, all rights reserved
 *
 * See License.txt for license.
 */

#pragma once

#include "CommandListener.h"

#include <memory>
#include <list>

class Actor;

/** Base class for "scenes."
 * A scene is a "place where action occurs." It can be a title screen, a loading screen, 
 * a cut-scene, or an entire world in which players, actors, and other objects interact. 
 *
 * At a technical level, a scene loads and manages all objects that exist in a scene. It
 * processes or passes on user inputs to the relevant objects, and performs any simulation,
 * Artificial Intelligence (AI) calculations, etc., that are needed to display the scene.
 * Scenes can also have audio.
 *
 * Child classes can set the playerAvatar, which is the object that user input will be 
 * forwarded, unless the command methods (e.g., goRight()) are overridden.
 */
class Scene : public CommandListener {
public:
	Scene();
	
	virtual ~Scene();
	
	/** Loads the resources needed to display this scene (e.g., the entire game level).
	 *
	 * @throws std::runtime_error if something went wrong
	 */
	virtual void loadResources();
	
	/** Frees up the resources used in this scene.
	 * The default behaviour is to empty this object of all items, e.g., the actors, playerAvatar, etc.
	 */
	virtual void freeResources();
	
	/** Called when the scene starts. 
	 * This should start any background music or sound, and perform any other initializaiton
	 * that isn't already handled by loadResources()
	 */
	virtual void start();
	
	/** Updates the scene.
	 * This should perform tasks such as:
	 * - Perform any Artificial Intelligence (AI) calculations
	 * - Update animation
	 * - Simulate the world, including triggering sound effects & maybe changing the music
	 *
	 * @return std::shared_ptr<Scene> the next scene, or nullptr if this scene 
	 */
	virtual std::shared_ptr<Scene> update();
	
	/** Returns true if the program should quit.
	 */
	virtual bool shouldQuit();
	
	/** Draws the scene to the display.
	 */
	virtual void draw();
	
	virtual void goUp();
	
	virtual void goLeft();
	
	virtual void goRight();
	
	virtual void goDown();
	
	virtual void goNowhere();
	
	virtual void doInteractWith();
	
	virtual void doExit();
	
protected:
	/** The player's avatar. 
	 * By default, all user input will be forwarded to the object that the player (user) is
	 * controlling.
	 */
	std::shared_ptr<CommandListener> playerAvatar;
	
	/** List of actors in the scene, ordered from top to bottom.
	 * NOTE: The player should also be in this list.
	 */
	std::list< std::shared_ptr<Actor> > actors;
	
	/** The ground's y position in pixels from the top of the screen.
	 */
	int groundYPos;
	
	/** Downward acceleration due to gravity.
	 */
	float gravity;
	
	bool exit;
};