#include "Asteroid.h"
#include <iostream>

//---------------------------------------------------------------------------
Asteroid::Asteroid(Ogre::SceneManager* sceneMgr) : GameObject(sceneMgr)
{
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
void Asteroid::addToScene(int i){
  std::stringstream entName;
  std::stringstream nodeName;
  std::string astEnt = "asteroidEntity";
  std::string astNode = "asteroidNode";
  entName << astEnt << i;
  nodeName << astNode << i;
  std::string resultEnt = entName.str();
  std::string resultNode = nodeName.str();
	entAsteroid = mSceneMgr->createEntity(resultEnt, "asteroid1.mesh");
  entAsteroid->setCastShadows(true);
  asteroidNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(resultNode, asteroidPosition);
  asteroidNode->attachObject(entAsteroid);
  float scale = 15.0f;
  asteroidNode->setScale(Ogre::Vector3(scale,scale,scale));
}
//---------------------------------------------------------------------------
void Asteroid::update(void){
  int outOfBounds = 0;
  if (asteroidPosition.x >= 750 || asteroidPosition.y >= 750 || asteroidPosition.z >= 750 || asteroidPosition.x <= -750 || asteroidPosition.y <= -750 || asteroidPosition.z <= -750) {
    outOfBounds = 1;
  }

  if (outOfBounds) {
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

	asteroidNode->translate(asteroidVelocity);
	GameObject::update();
}
//---------------------------------------------------------------------------