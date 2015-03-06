#include <OgreMath.h>
#include "Ship.h"

//---------------------------------------------------------------------------
Ship::Ship(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim, Ogre::SceneNode* cam) : GameObject(nym, mgr, sim)
{
	cameraNode = cam;
	//rootNode->getParent()->removeChild(rootNode);
	//cameraNode->addChild(rootNode);
	rootNode = cameraNode;
	left = false;
	right = false;
}
//---------------------------------------------------------------------------
Ship::~Ship(void)
{
}
//---------------------------------------------------------------------------
void Ship::addToScene(void)
{
	geom = sceneMgr->createEntity("shipEnt", "rocket.mesh");
	geom->setCastShadows(true);
	rootNode->attachObject(geom);

	mass = 3.0f;
	shape = new btCapsuleShapeZ(3.0f, 15.0f);
}
//---------------------------------------------------------------------------
void Ship::addToSimulator(void)
{
	GameObject::addToSimulator();

	body->setLinearFactor(btVector3(1,0,0));
	body->setAngularFactor(btVector3(0,0,0));
}
//---------------------------------------------------------------------------
void Ship::update(void)
{
	if (left && body->getLinearVelocity().getX() < 250) {
		body->applyCentralForce(btVector3(1000,0,0));
	}
	if (right && body->getLinearVelocity().getX() > -250) {
		body->applyCentralForce(btVector3(-1000,0,0));
	}
}
//---------------------------------------------------------------------------
void Ship::injectKeyDown(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_Q){
		left = true;
		
	}
	if (arg.key == OIS::KC_E){
		right = true;
	}
}
//---------------------------------------------------------------------------
void Ship::injectKeyUp(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_Q){
		left = false;
	}
	if (arg.key == OIS::KC_E){
		right = false;
	}
}
//---------------------------------------------------------------------------