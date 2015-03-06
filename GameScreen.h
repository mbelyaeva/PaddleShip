#ifndef __GameScreen_h_
#define __GameScreen_h_

#include <Ogre.h>
#include "BaseApplication.h" //?
#include "Ship.h"
#include "AsteroidSys.h"
#include "Simulator.h"
#include "Paddle.h"

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
	Paddle* paddle;
	btHingeConstraint* paddleHinge;
	AsteroidSys* ast1;

	bool motorRight;


};

//---------------------------------------------------------------------------

#endif // #ifndef __GameScreen_h_

//---------------------------------------------------------------------------