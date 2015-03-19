#include <OgreMath.h>
#include "Alien.h"
#include <iostream>
//---------------------------------------------------------------------------
Alien::Alien(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim, Ogre::SceneNode* cam, int &ht, std::deque<GameObject*>* oList, SoundPlayer* sPlayer) : GameObject(nym, mgr, sim), health(ht)
{
	cameraNode = cam;
	objList = oList;
	//rootNode->getParent()->removeChild(rootNode);
	//cameraNode->addChild(rootNode);
	//rootNode = cameraNode;
	//health = 100;
	hasAsteroid = false;
	left = false;
	right = false;
	soundPlayer = sPlayer;
	float minP = 1;
  	float maxP = 5;
  	Ogre::Real xP = minP + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxP-minP)));
  	minP = 30;
  	maxP = 40;
  	Ogre::Real zP = minP + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxP-minP)));
	rootNode->setPosition(Ogre::Vector3(xP, 0, 25));
}
//---------------------------------------------------------------------------
Alien::~Alien(void)
{
}
//---------------------------------------------------------------------------
void Alien::addToScene(void)
{
	geom = sceneMgr->createEntity("AlienEnt", "rocket.mesh");
	geom->setCastShadows(true);
	rootNode->attachObject(geom);

	mass = 3.0f;
	shape = new btCapsuleShapeZ(3.0f, 15.0f);
}
//---------------------------------------------------------------------------
void Alien::addToSimulator(void)
{
	GameObject::addToSimulator();

	body->setLinearFactor(btVector3(1,0,0));
	body->setAngularFactor(btVector3(0,0,0));
}
//---------------------------------------------------------------------------
void Alien::update(void)
{
	if (left && body->getLinearVelocity().getX() < 250) {
		body->applyCentralForce(btVector3(1000,0,0));
	}
	if (right && body->getLinearVelocity().getX() > -250) {
		body->applyCentralForce(btVector3(-1000,0,0));
	}
	if (context->hit){
		//lose health
		if (health > 0) {
			health = 0;
		}
		std::stringstream healthVal;
 		healthVal << "" << health;
 		if (mDetailsPanel==NULL) {
 	 		printf("mDetailsPanel is null ptr\n");
 	 	}
 	 	mDetailsPanel->setParamValue(2, healthVal.str());
		soundPlayer->playShipHit();
	}
}
//---------------------------------------------------------------------------
void Alien::injectKeyDown(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_J){
		left = true;
		
	}
	if (arg.key == OIS::KC_L){
		right = true;
	}
	if (arg.key == OIS::KC_I){
		if (!hasAsteroid) {
			grabAsteroid(true);	
		}
	}
}
//---------------------------------------------------------------------------
void Alien::injectKeyUp(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_J){
		left = false;
	}
	if (arg.key == OIS::KC_L){
		right = false;
	}
	if (arg.key == OIS::KC_I){
		grabAsteroid(false);		
	}
}
//---------------------------------------------------------------------------
void Alien::setDeetsPan(OgreBites::ParamsPanel*mDeetsPan)
{
	mDetailsPanel = mDeetsPan;
}
//---------------------------------------------------------------------------
Ogre::Vector3 Alien::getPos()
{
	return rootNode->getPosition();
}
//---------------------------------------------------------------------------

void Alien::grabAsteroid(bool tryGrab)
{
	if (tryGrab) {
		std::deque<GameObject*> oList = *objList;
		for (int i = 3; i < oList.size(); i++) {
			if ((oList[i] -> getPos()).z <= ((rootNode ->getPosition()).z + 10) && (oList[i] -> getPos()).z >= (rootNode ->getPosition()).z) {
				hasAsteroid = true;
				//reset rigid body as child node of alien ship
			}
		}
	}
}

//---------------------------------------------------------------------------