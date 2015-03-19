#ifndef __Alien_h_
#define __Alien_h_

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISKeyboard.h>
#else
#  include <OISEvents.h>
#  include <OISKeyboard.h>
#endif

#include "GameObject.h"
#include "SoundPlayer.h"
#include <SdkTrays.h>

//---------------------------------------------------------------------------

class Alien: public GameObject 
{
public:
	Alien(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim, Ogre::SceneNode* cam, int &ht, std::deque<GameObject*>* oList, SoundPlayer* sPlayer);
	~Alien(void);
	void addToScene(void);
	void addToSimulator(void);
	void update(void);
	void setDeetsPan(OgreBites::ParamsPanel*mDeetsPan);
	void injectKeyDown(const OIS::KeyEvent &arg);
	void injectKeyUp(const OIS::KeyEvent &arg);
	void grabAsteroid(bool tryGrab);
	Ogre::Vector3 getPos();

protected:
	Ogre::SceneNode* cameraNode;
	OgreBites::ParamsPanel* mDetailsPanel;
	SoundPlayer* soundPlayer;
	std::deque<GameObject*>* objList;
	//int health; 
	bool left;
	bool right;
	int &health;
	bool hasAsteroid;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Alien_h_

//---------------------------------------------------------------------------