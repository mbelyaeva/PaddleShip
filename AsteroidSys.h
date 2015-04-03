#ifndef __AsteroidSys_h_
#define __AsteroidSys_h_

#include "Asteroid.h"
#define NUM_ASTEROIDS 250

//---------------------------------------------------------------------------

class AsteroidSys
{
public:
	AsteroidSys(Ogre::SceneManager* mgr, Simulator* sim, Ship * sh);
	virtual ~AsteroidSys(void);
	void update(void);
	void addToScene(void);
	void addToSimulator(btDiscreteDynamicsWorld* dynamicsWorld);
protected:
	Asteroid * asteroidSystem [NUM_ASTEROIDS];
};

//---------------------------------------------------------------------------

#endif // #ifndef __AsteroidSys_h_

//---------------------------------------------------------------------------