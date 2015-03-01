#include "AsteroidSys.h"

//---------------------------------------------------------------------------
AsteroidSys::AsteroidSys(Ogre::SceneManager* mgr, Simulator* sim)
{
  for (int i = 0; i < 5; i++) {
    std::stringstream nodeName;
    nodeName << "asteroidNode" << i;
    asteroidSystem[i] = new Asteroid(nodeName.str(), mgr, sim);
  }

}
//---------------------------------------------------------------------------
AsteroidSys::~AsteroidSys(void)
{
  for (int i = 0; i < 5; i++) {
    delete asteroidSystem[i];
  }
  //delete [] asteroidSystem;
}
//---------------------------------------------------------------------------
void AsteroidSys::update(void){
  for (int i=0; i <5; i++) {
    asteroidSystem[i]-> update();
  }
}
//---------------------------------------------------------------------------
void AsteroidSys::addToScene(void){
  for (int i=0; i <5; i++) {
    asteroidSystem[i]-> addToScene(i);
  }
}
//---------------------------------------------------------------------------