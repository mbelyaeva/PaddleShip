#ifndef __Asteroid_h_
#define __Asteroid_h_

#include "GameObject.h"
#include <Ogre.h>

//---------------------------------------------------------------------------

class Asteroid: public GameObject 
{
public:
	Asteroid(Ogre::SceneManager* sceneMgr);
	~Asteroid(void);
	void createScene(void);
	void update(void);

protected:
	Ogre::SceneManager* mSceneMgr;
	Ogre::Entity *entAsteroid;
	Ogre::SceneNode *asteroidNode;
	Ogre::Vector3 asteroidVelocity;
	Ogre::Vector3 asteroidPosition;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Asteroid_h_

//---------------------------------------------------------------------------