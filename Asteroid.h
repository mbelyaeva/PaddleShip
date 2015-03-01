#ifndef __Asteroid_h_
#define __Asteroid_h_

#include <Ogre.h>
#include <stdlib.h>
#include "GameObject.h"
#include "Simulator.h"


//---------------------------------------------------------------------------

class Asteroid: public GameObject 
{
public:
	Asteroid(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim);
	~Asteroid(void);
	void addToScene(int i);
	void update(void);

protected:
	Ogre::Vector3 asteroidVelocity;
	Ogre::Vector3 asteroidPosition;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Asteroid_h_

//---------------------------------------------------------------------------