#include "Asteroid.h"

//---------------------------------------------------------------------------
AsteroidSys::AsteroidSys(Ogre::SceneManager* sceneMgr)
{
	mSceneMgr = sceneMgr;
  for (int i = 0; i < 5; i++) {
    asteroidSystem[i] = new Asteroid(mSceneMgr);
  }

}
//---------------------------------------------------------------------------
AsteroidSys::~AsteroidSys(void)
{
  delete [] asteroidSystem;
}
//---------------------------------------------------------------------------
void AsteroidSys::update(const Ogre::FrameEvent &evt){
  for (int i=0; i <5; i++) {
    asteroidSystem[i]-> update();
  }
}
//---------------------------------------------------------------------------