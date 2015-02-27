#ifndef __AsteroidSys_h_
#define __AsteroidSys_h_

#include "Asteroid.h"


//---------------------------------------------------------------------------

class AsteroidSys
{
public:
	AsteroidSys(Ogre::SceneManager* sceneMgr);
	virtual ~AsteroidSys(void);
	void update(void);
	void addToScene(void);
protected:
	Ogre::SceneManager* mSceneMgr;
	Asteroid * asteroidSystem [5];
};

//---------------------------------------------------------------------------

#endif // #ifndef __AsteroidSys_h_

//---------------------------------------------------------------------------