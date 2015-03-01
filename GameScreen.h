#ifndef __GameScreen_h_
#define __GameScreen_h_

#include <Ogre.h>
#include "BaseApplication.h" //?
#include "Ship.h"
#include "AsteroidSys.h"
#include "Simulator.h"

//---------------------------------------------------------------------------

class GameScreen
{
public:
	GameScreen(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* cameraNode);
	virtual ~GameScreen(void);
	void createScene(void);
	void update(const Ogre::FrameEvent &evt);

	void injectKeyDown(const OIS::KeyEvent &arg);
	void injectKeyUp(const OIS::KeyEvent &arg);
	void injectMouseMove(const OIS::MouseEvent &arg);
	void injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	void injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

protected:
	Ogre::SceneManager* mSceneMgr;

	Simulator* sim;
	Ship* ship;
	AsteroidSys* ast1;


};

//---------------------------------------------------------------------------

#endif // #ifndef __GameScreen_h_

//---------------------------------------------------------------------------