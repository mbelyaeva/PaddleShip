#include "Ship.h"

//---------------------------------------------------------------------------
Ship::Ship(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim, Ogre::SceneNode* cameraNode) : GameObject(nym, mgr, sim)
{
	velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	rootNode = cameraNode; //probably change later
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
	float scale = 1.0f;
	rootNode->setScale(Ogre::Vector3(scale,scale,-scale));

	mass = 0.0f; //kinematic
	shape = new btCapsuleShape(5.0f, 25.0f);

}
//---------------------------------------------------------------------------
void Ship::update(void)
{
	//rootNode->translate(velocity);
	//GameObject::update();
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