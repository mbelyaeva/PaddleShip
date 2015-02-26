#ifndef __Asteroid_h_
#define __Asteroid_h_

#include "GameObject.h"
#include <Ogre.h>
#include <stdlib.h>

//---------------------------------------------------------------------------

class Asteroid: public GameObject 
{
public:
	Asteroid(Ogre::SceneManager* sceneMgr);
	~Asteroid(void);
	void addToScene(int i);
	void update(void);

protected:
	Ogre::Entity *entAsteroid;
	Ogre::SceneNode *asteroidNode;
	Ogre::Vector3 asteroidVelocity;
	Ogre::Vector3 asteroidPosition;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Asteroid_h_

//---------------------------------------------------------------------------