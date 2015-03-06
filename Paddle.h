#ifndef __Paddle_h_
#define __Paddle_h_

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISKeyboard.h>
#else
#  include <OISEvents.h>
#  include <OISKeyboard.h>
#endif

#include "GameObject.h"

//---------------------------------------------------------------------------

class Paddle: public GameObject 
{
public:
	Paddle(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim, Ogre::SceneNode* shipNode);
	~Paddle(void);
	void addToScene(void);
	void addToSimulator(void);
	void update(void);

	void injectKeyDown(const OIS::KeyEvent &arg);
	void injectKeyUp(const OIS::KeyEvent &arg);

protected:
	Ogre::SceneNode* mShipNode;

};

//---------------------------------------------------------------------------

#endif // #ifndef __Paddle_h_

//---------------------------------------------------------------------------