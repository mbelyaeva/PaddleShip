#include "Asteroid.h"
#include <iostream>
#include <cassert>

//---------------------------------------------------------------------------
Asteroid::Asteroid(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim) : GameObject(nym, mgr, sim)
{
  float minV = 20;
  float maxV = 30;
  Ogre::Real zV = minV + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxV-minV)));
  minV = -3;
  maxV = 3;
  Ogre::Real xV = minV + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxV-minV)));
  asteroidVelocity = Ogre::Vector3(xV,0,zV);
  float minP = -40;
  float maxP = 40;
  Ogre::Real xP = minP + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxP-minP)));
  asteroidPosition = Ogre::Vector3(xP,0,minP*2);
  rootNode->setPosition(asteroidPosition);
}
//---------------------------------------------------------------------------
Asteroid::~Asteroid(void)
{
}
//---------------------------------------------------------------------------
void Asteroid::addToScene(int i){
  std::stringstream entName;
  entName << "asteroidEntity" << i;
  std::stringstream meshName;
  meshName << "asteroid" << (i%3)+1 << ".mesh";

  geom = sceneMgr->createEntity(entName.str(), meshName.str());
  geom->setCastShadows(true);

  rootNode->attachObject(geom);
  float scale = 1.0f;

  rootNode->setScale(Ogre::Vector3(scale,scale,scale));

  mass = 1.0f;
  shape = new btSphereShape(scale*10);
}
//---------------------------------------------------------------------------
void Asteroid::update(void){

  /*if (asteroidPosition.x >= 750 || asteroidPosition.y >= 750 || asteroidPosition.z >= 750 || asteroidPosition.x <= -750 || asteroidPosition.y <= -750 || asteroidPosition.z <= -750) {
    float minV = 1;
    float maxV = 3;
    Ogre::Real zV = minV + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxV-minV)));
    minV = -1;
    maxV = 1;
    Ogre::Real xV = minV + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxV-minV)));
    asteroidVelocity = Ogre::Vector3(xV,0,zV);
    float minP = -650;
    float maxP = 650;
    Ogre::Real xP = minP + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxP-minP)));
    asteroidPosition = Ogre::Vector3(xP,0,minP);
    rootNode->setPosition(asteroidPosition);
  }

	rootNode->translate(asteroidVelocity);
  asteroidPosition = rootNode->getPosition();*/
	//GameObject::update();
}
//---------------------------------------------------------------------------
void Asteroid::addToSimulator(void){
  GameObject::addToSimulator();
  body->setLinearVelocity( btVector3(asteroidVelocity.x, asteroidVelocity.y, asteroidVelocity.z) );
}
//---------------------------------------------------------------------------