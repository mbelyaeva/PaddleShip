#include <OgreMath.h>
#include "Ship.h"
#include <iostream>
//---------------------------------------------------------------------------
Ship::Ship(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim, Ogre::SceneNode* cam, int &sc, SoundPlayer* sPlayer) : GameObject(nym, mgr, sim), score(sc)
{
	cameraNode = cam;
	hasDecr = false;
	//rootNode->getParent()->removeChild(rootNode);
	//cameraNode->addChild(rootNode);
	rootNode = cameraNode;
	health = 100;
	left = false;
	right = false;
	soundPlayer = sPlayer;
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

	mass = 10.0f;
	shape = new btCapsuleShapeZ(3.0f, 15.0f);
}
//---------------------------------------------------------------------------
void Ship::addToSimulator(void)
{
	GameObject::addToSimulator();

	body->setLinearFactor(btVector3(1,0,1));
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
	if (forward && body->getLinearVelocity().getZ() < 250) {
		body->applyCentralForce(btVector3(0,0,1000));
	}
	if (back && body->getLinearVelocity().getZ() > -250) {
		body->applyCentralForce(btVector3(0,0,-1000));
	}
	if(!context->hit) {
		hasDecr = false;
	}
	if (!hasDecr && context->hit){
		//lose health
		if (score > 0) {
			score-=1;
		}
		std::stringstream scoreVal;
 		scoreVal << "" << score;
 		if (mDetailsPanel==NULL) {
 	 		printf("mDetailsPanel is null ptr\n");
 	 	}
 	 	mDetailsPanel->setParamValue(0, scoreVal.str());
		soundPlayer->playShipHit();
		hasDecr = true;
	}
}
//---------------------------------------------------------------------------
void Ship::injectKeyDown(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_A){
		left = true;
		
	}
	if (arg.key == OIS::KC_D){
		right = true;
	}
	if (arg.key == OIS::KC_W){
		forward = true;
	}
	if (arg.key == OIS::KC_S){
		back = true;
	}
}
//---------------------------------------------------------------------------
void Ship::injectKeyUp(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_A){
		left = false;
	}
	if (arg.key == OIS::KC_D){
		right = false;
	}
	if (arg.key == OIS::KC_W){
		forward = false;
	}
	if (arg.key == OIS::KC_S){
		back = false;
	}
}
//---------------------------------------------------------------------------
void Ship::setDeetsPan(OgreBites::ParamsPanel*mDeetsPan)
{
	mDetailsPanel = mDeetsPan;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/*
Ogre::Vector3 Ship::getPos()
{
	return GameObject::getPos();
}
*/
