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
	/*
	if (arg.key == OIS::KC_I){
		grabAsteroid(false);
		hasAsteroid = false;		
	}
	*/
}
//---------------------------------------------------------------------------
void Alien::setDeetsPan(OgreBites::ParamsPanel*mDeetsPan)
{
	mDetailsPanel = mDeetsPan;
}
//---------------------------------------------------------------------------
/*
Ogre::Vector3 Alien::getPos()
{
	return rootNode->getPosition();
}
//---------------------------------------------------------------------------
*/

void Alien::grabAsteroid(bool tryGrab)
{
	if (tryGrab) {
		std::deque<GameObject*> oList = *objList;
		for (int i = 3; i < oList.size(); i++) {
			if (!hasAsteroid && (oList[i] -> getPos()).z <= ((rootNode ->getPosition()).z - 20) && ((oList[i] -> getPos()).z <= (rootNode ->getPosition()).z) && (oList[i] -> getPos()).x <= ((rootNode ->getPosition()).x + 20) && (oList[i] -> getPos()).x >= ((rootNode ->getPosition()).x - 20)) {
				hasAsteroid = true;
				//reset rigid body as child node of alien ship
				Asteroid * ast1 = (Asteroid *) oList[i];
				ast1 -> getDynamicsWorld() -> removeRigidBody(ast1 -> getBody());
				delete ast1 -> getBody() -> getMotionState();
   	 			delete ast1 -> getBody();
   	 			Ogre::Vector3 alienPos = getPos();
				ast1 -> getTransform() -> setOrigin(btVector3(alienPos.x, alienPos.y, alienPos.z));
				//printf("set origin\n");
				Ogre::Quaternion qt = ast1 -> getNode()->getOrientation();
				//printf("set orientation\n");
				ast1 -> getTransform() -> setRotation(btQuaternion(qt.x, qt.y, qt.z, qt.w));
				//printf("set rotation\n");
				ast1 -> setMotionState(new OgreMotionState(*(ast1 -> getTransform()), ast1 -> getNode()));
				//printf("created new motionState\n");
				//shape = new btSphereShape(sphereSize);
				//printf("reset shape\n");
				//printf("mass is %f before reset\n", massVal);  
				//mass = massVal;
				//printf("mass is %f\n", massVal);
				//printf("reset mass\n");
				btRigidBody::btRigidBodyConstructionInfo rbInfo(ast1 -> getMass(), ast1 -> getMotionState(), ast1 -> getShape(), ast1 -> getInertia());
				//printf("constructed rigid body\n");
				rbInfo.m_restitution = ast1 -> getRestitution();
				rbInfo.m_friction = ast1 -> getFriction();
				//printf("reassigned restitution and friction\n");
				ast1 -> setBody(new btRigidBody(rbInfo));
				//printf("created new rigid body\n");
				//printf("Velocity values are now: %f, %f, %f\n", asteroidVelocity.x, asteroidVelocity.y, asteroidVelocity.z);
				//body->setLinearVelocity( btVector3(asteroidVelocity.x, asteroidVelocity.y, asteroidVelocity.z) );
				ast1 -> getDynamicsWorld() -> addRigidBody(ast1 -> getBody());
				//asteroidBinder = new btFixedConstraint(*body, *(ast1 -> getBody()), tr, *(ast1 -> getTransform());

				/*
				asteroidBinder = new btGeneric6DofConstraint(body, ast1 -> getBody(), &tr, ast1 -> getTransform(), true);
		
 				// lock all axes
	 			for (int j = 0; j < 6; j++)
		 			asteroidBinder->setLimit(j, 0, 0);
				break;
				*/
				asteroidBinder = new btHingeConstraint(*body, *ast1 -> getBody(), btVector3(0,0,0), btVector3(0,0,0), btVector3(0,1,0), btVector3(0,1,0));
				asteroidBinder->setLimit(M_PI/2, M_PI/2);
				ast1 -> getDynamicsWorld() ->addConstraint(asteroidBinder, true);
			}
		}
	}
}

//---------------------------------------------------------------------------