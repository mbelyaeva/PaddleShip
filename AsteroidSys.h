#ifndef __AsteroidSys_h_
#define __AsteroidSys_h_

#include "Asteroid.h"


//---------------------------------------------------------------------------

class AsteroidSys
{
public:
	AsteroidSys(Ogre::SceneManager* mgr, Simulator* sim);
	virtual ~AsteroidSys(void);
	void update(void);
	void addToScene(void);
	void addToSimulator(btDiscreteDynamicsWorld* dynamicsWorld);
protected:
	Asteroid * asteroidSystem [5];
};

//---------------------------------------------------------------------------

#endif // #ifndef __AsteroidSys_h_

//---------------------------------------------------------------------------