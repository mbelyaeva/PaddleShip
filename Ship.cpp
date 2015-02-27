#include "Ship.h"

//---------------------------------------------------------------------------
Ship::Ship(Ogre::SceneManager* sceneMgr) : GameObject(sceneMgr)
{
	velocity = Ogre::Vector3(0,0,0);

}
//---------------------------------------------------------------------------
Ship::~Ship(void)
{
}
//---------------------------------------------------------------------------
void Ship::addToScene(void){
	name = "shipEntity";
	geom = mSceneMgr->createEntity(name, "sphere.mesh");
	geom->setCastShadows(true);
	shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("shipNode", Ogre::Vector3(0, 0, 0));
	shipNode->attachObject(geom);
	int scale = 1.0f;
	shipNode->setScale(Ogre::Vector3(scale,scale,scale));
}
//---------------------------------------------------------------------------
void Ship::update(void){
	shipNode->translate(velocity);
	GameObject::update();
}
//---------------------------------------------------------------------------