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
	geom = sceneMgr->createEntity("AlienEnt", "alien.mesh");
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
	if (arg.key == OIS::KC_LEFT){
		if (hasAsteroid) {
			shootAsteroid(arg);	
		}
	}
	if (arg.key == OIS::KC_RIGHT){
		if (hasAsteroid) {
			shootAsteroid(arg);	
		}
	}
	if (arg.key == OIS::KC_UP){
		if (hasAsteroid) {
			shootAsteroid(arg);	
		}
	}
	if (arg.key == OIS::KC_DOWN){
		if (hasAsteroid) {
			shootAsteroid(arg);	
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
				currentAsteroid = (Asteroid *) oList[i];
				currentAsteroid -> getDynamicsWorld() -> removeRigidBody(currentAsteroid -> getBody());
				delete currentAsteroid -> getBody() -> getMotionState();
   	 			delete currentAsteroid -> getBody();
   	 			Ogre::Vector3 alienPos = getPos();
   	 			//currentAsteroid -> getNode() ->setPosition(astPos);
				currentAsteroid -> getTransform() -> setOrigin(btVector3(alienPos.x, alienPos.y + 17, alienPos.z));
				//printf("set origin\n");
				Ogre::Quaternion qt = currentAsteroid -> getNode()->getOrientation();
				//printf("set orientation\n");
				currentAsteroid -> getTransform() -> setRotation(btQuaternion(qt.x, qt.y, qt.z, qt.w));
				//printf("set rotation\n");
				currentAsteroid -> setMotionState(new OgreMotionState(*(currentAsteroid -> getTransform()), currentAsteroid -> getNode()));
				//printf("created new motionState\n");
				//shape = new btSphereShape(sphereSize);
				//printf("reset shape\n");
				//printf("mass is %f before reset\n", massVal);  
				//mass = massVal;
				//printf("mass is %f\n", massVal);
				//printf("reset mass\n");
				btRigidBody::btRigidBodyConstructionInfo rbInfo(currentAsteroid -> getMass(), currentAsteroid -> getMotionState(), currentAsteroid -> getShape(), currentAsteroid -> getInertia());
				//printf("constructed rigid body\n");
				rbInfo.m_restitution = currentAsteroid -> getRestitution();
				rbInfo.m_friction = currentAsteroid -> getFriction();
				//printf("reassigned restitution and friction\n");
				currentAsteroid -> setBody(new btRigidBody(rbInfo));
				//printf("created new rigid body\n");
				//printf("Velocity values are now: %f, %f, %f\n", asteroidVelocity.x, asteroidVelocity.y, asteroidVelocity.z);
				//body->setLinearVelocity( btVector3(asteroidVelocity.x, asteroidVelocity.y, asteroidVelocity.z) );
				currentAsteroid -> getDynamicsWorld() -> addRigidBody(currentAsteroid -> getBody());
				//asteroidBinder = new btFixedConstraint(*body, *(currentAsteroid -> getBody()), tr, *(currentAsteroid -> getTransform());

				/*
				asteroidBinder = new btGeneric6DofConstraint(body, currentAsteroid -> getBody(), &tr, currentAsteroid -> getTransform(), true);
		
 				// lock all axes
	 			for (int j = 0; j < 6; j++)
		 			asteroidBinder->setLimit(j, 0, 0);
				break;
				*/
				asteroidBinder = new btHingeConstraint(*body, *currentAsteroid -> getBody(), btVector3(0,0,0), btVector3(0,-17,0), btVector3(0,1,0), btVector3(0,1,0));
				asteroidBinder->setLimit(M_PI/2, M_PI/2);
				currentAsteroid -> getDynamicsWorld() ->addConstraint(asteroidBinder, true);
			}
		}
	}
}

//---------------------------------------------------------------------------

void Alien::shootAsteroid(const OIS::KeyEvent &arg) {
	currentAsteroid -> getDynamicsWorld() ->removeConstraint(asteroidBinder);
	//delete asteroidBinder;
	if (arg.key == OIS::KC_LEFT){
		currentAsteroid -> getBody()->setLinearVelocity(btVector3(200,0,0));
	} else if (arg.key == OIS::KC_RIGHT){
		currentAsteroid -> getBody()->setLinearVelocity(btVector3(-200,0,0));
	} else if (arg.key == OIS::KC_UP){
		currentAsteroid -> getBody()->setLinearVelocity(btVector3(0,0,200));
	} else if (arg.key == OIS::KC_DOWN){
		currentAsteroid -> getBody()->setLinearVelocity(btVector3(0,0,-200));
	}
	hasAsteroid = false;
}