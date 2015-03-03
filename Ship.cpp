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
	geom = sceneMgr->createEntity("shipEnt", "rocket.mesh"); //geom = sceneMgr->createEntity("shipEntity", "sphere.mesh");
	geom->setCastShadows(true);
	//geom->setMaterialName("Examples/Rockwall");
	//rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("rootNode", Ogre::Vector3(0, 0, 0));
	rootNode->attachObject(geom);
	int scale = 15.0f;
	rootNode->setScale(Ogre::Vector3(scale,scale,-scale));

	mass = 1.0f;
	shape = new btSphereShape(15.0f);

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