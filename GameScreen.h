#ifndef __GameScreen_h_
#define __GameScreen_h_

#include <Ogre.h>
#include "BaseApplication.h" //?
#include "Ship.h"
#include "Asteroid.h"

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

	Ship* ship;
	Asteroid* ast1;


};

//---------------------------------------------------------------------------

#endif // #ifndef __GameScreen_h_

//---------------------------------------------------------------------------