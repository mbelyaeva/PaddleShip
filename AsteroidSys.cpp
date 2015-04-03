#include "AsteroidSys.h"

//---------------------------------------------------------------------------
AsteroidSys::AsteroidSys(Ogre::SceneManager* mgr, Simulator* sim, Ship * sh)
{
  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    std::stringstream nodeName;
    nodeName << "asteroidNode" << i;
    asteroidSystem[i] = new Asteroid(nodeName.str(), mgr, sim, sh);
  }

}
//---------------------------------------------------------------------------
AsteroidSys::~AsteroidSys(void)
{
  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    delete asteroidSystem[i];
  }
  //delete [] asteroidSystem;
}
//---------------------------------------------------------------------------
void AsteroidSys::update(void){
  for (int i=0; i <NUM_ASTEROIDS; i++) {
    asteroidSystem[i]-> update();
  }
}
//---------------------------------------------------------------------------
void AsteroidSys::addToScene(void){
  for (int i=0; i <NUM_ASTEROIDS; i++) {
    asteroidSystem[i]-> addToScene(i);
  }
}
//---------------------------------------------------------------------------
void AsteroidSys::addToSimulator(btDiscreteDynamicsWorld* dynamicsWorld){
  for (int i=0; i <NUM_ASTEROIDS; i++) {
    asteroidSystem[i]-> addToSimulator();
    asteroidSystem[i]-> setDynamicsWorld(dynamicsWorld);
  }
}
