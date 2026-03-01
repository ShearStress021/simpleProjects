/** ScarfyScene.h
 *
 * @author Hans de Ruiter
 *
 * @copyright (c) 2022 by Kea Sigma Delta Limited, all rights reserved
 *
 * See License.txt for license.
 */

#pragma once

#include "Scene.h"
#include "Scarfy.h"

/** A scene for scarfy to walk around in.
 */
class ScarfyScene : public Scene {
public:
	ScarfyScene();
	
	virtual ~ScarfyScene();
	
	virtual void loadResources();
};

