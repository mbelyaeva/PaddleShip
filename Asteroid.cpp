#include "Asteroid.h"

//---------------------------------------------------------------------------
Asteroid::Asteroid(Ogre::SceneManager* sceneMgr)
{
  mSceneMgr = sceneMgr;
  srand(time(NULL));
  float minV = 1;
  float maxV = 3;
  Ogre::Real zV = minV + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxV-minV)));
  Ogre::Real xV = minV + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxV-minV)));
  asteroidVelocity = Ogre::Vector3(xV,0,zV);
  float minP = -650;
  float maxP = 650;
  Ogre::Real xP = minP + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxP-minP)));
  asteroidPosition = Ogre::Vector3(xP,0,minP);
}
//---------------------------------------------------------------------------
Asteroid::~Asteroid(void)
{
}
//---------------------------------------------------------------------------
void Asteroid::createScene(void){
	entAsteroid = mSceneMgr->createEntity("asteroidEntity", "sphere.mesh");
  entAsteroid->setCastShadows(true);
  asteroidNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("asteroidNode", asteroidPosition);
  asteroidNode->attachObject(entAsteroid);
  asteroidNode->setScale(Ogre::Vector3(0.5f,0.5f,0.5f));
  entAsteroid->setMaterialName("Examples/Rockwall");
}
//---------------------------------------------------------------------------
void Asteroid::update(void){
	asteroidNode->translate(asteroidVelocity);
	GameObject::update();
}
//---------------------------------------------------------------------------