#include "Ship.h"

//---------------------------------------------------------------------------
Ship::Ship(Ogre::SceneManager* sceneMgr) : GameObject(sceneMgr)
{

}
//---------------------------------------------------------------------------
Ship::~Ship(void)
{
}
//---------------------------------------------------------------------------
void Ship::addToScene(void){
  entShip = mSceneMgr->createEntity("shipEntity", "sphere.mesh");
  entShip->setCastShadows(true);
  shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("shipNode", Ogre::Vector3(0, 0, 0));
  shipNode->attachObject(entShip);
  int scale = 1.0f;
  shipNode->setScale(Ogre::Vector3(scale,scale,scale));
}
//---------------------------------------------------------------------------
void Ship::update(void){
	shipNode->translate(velocity);
	GameObject::update();
}
//---------------------------------------------------------------------------