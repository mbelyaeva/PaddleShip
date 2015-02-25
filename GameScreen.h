#ifndef __GameScreen_h_
#define __GameScreen_h_

#include <Ogre.h>
#include "BaseApplication.h"

//---------------------------------------------------------------------------

class GameScreen
{
public:
	GameScreen(Ogre::SceneManager* sceneMgr);
	virtual ~GameScreen(void);
	void createScene(void);
	void update(const Ogre::FrameEvent &evt);

protected:
	Ogre::SceneManager* mSceneMgr;

	Ogre::Entity *entShip;
	Ogre::SceneNode *shipNode;
};

//---------------------------------------------------------------------------

#endif // #ifndef __GameScreen_h_

//---------------------------------------------------------------------------