/** MainMenuScene.h
 *
 * @author Hans de Ruiter
 *
 * @copyright (c) 2022 by Kea Sigma Delta Limited, all rights reserved
 *
 * See License.txt for license.
 */

#pragma once

#include "Scene.h"

/** The game's main menu.
 */
class MainMenuScene : public Scene {
public:
	MainMenuScene();
	
	virtual ~MainMenuScene();
	
	virtual std::shared_ptr<Scene> update();
	
	virtual bool shouldQuit();
	
	virtual void draw();
	
	virtual void doExit();
	
private:
	bool startClicked;
	bool quit;
};

