#include "Ship.h"

//---------------------------------------------------------------------------
Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* cameraNode) : GameObject(sceneMgr)
{
	velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	shipNode = cameraNode; //probably change later
}
//---------------------------------------------------------------------------
Ship::~Ship(void)
{
}
//---------------------------------------------------------------------------
void Ship::addToScene(void)
{
	name = "shipEntity";
	geom = mSceneMgr->createEntity(name, "sphere.mesh");
	geom->setCastShadows(true);
	//shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("shipNode", Ogre::Vector3(0, 0, 0));
	shipNode->attachObject(geom);
	int scale = 1.0f;
	shipNode->setScale(Ogre::Vector3(scale,scale,scale));
}
//---------------------------------------------------------------------------
void Ship::update(void)
{
	shipNode->translate(velocity);
	GameObject::update();
}
//---------------------------------------------------------------------------
void Ship::injectKeyDown(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_A){
		velocity += Ogre::Vector3(-2.0f, 0.0f, 0.0f);
	}
	if (arg.key == OIS::KC_D){
		velocity += Ogre::Vector3(2.0f, 0.0f, 0.0f);
	}
}
//---------------------------------------------------------------------------
void Ship::injectKeyUp(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_A){
		velocity -= Ogre::Vector3(-2.0f, 0.0f, 0.0f);
	}
	if (arg.key == OIS::KC_D){
		velocity -= Ogre::Vector3(2.0f, 0.0f, 0.0f);
	}
}
//---------------------------------------------------------------------------