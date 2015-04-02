#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* cameraNode, SoundPlayer* sPlayer)
{
	score = 0;
	alienHealth = 100;
	mSceneMgr = sceneMgr;
	soundPlayer = sPlayer;
	sim = new Simulator(sceneMgr);
	std::deque<GameObject*>* objList = sim -> getObjList();
	ship = new Ship("Ship", sceneMgr, sim, cameraNode, score, sPlayer);
	alien = new Alien("Alien", sceneMgr, sim, cameraNode, alienHealth, objList, sPlayer);
	paddle = new Paddle("paddle", sceneMgr, sim, score, sPlayer); 
	ast1 = new AsteroidSys(sceneMgr, sim, ship);
	motorRight = true;
}
//---------------------------------------------------------------------------
GameScreen::~GameScreen(void)
{
	delete ship;
	delete alien;
	delete paddle;
	delete ast1;
	delete sim;
}
//---------------------------------------------------------------------------
void GameScreen::createScene(void)
{
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
	
	//ship
	ship->addToScene();
	ship->addToSimulator();

	//paddle
	paddle->addToScene();
	paddle->addToSimulator();

	paddleHinge = new btHingeConstraint(*ship->getBody(), *paddle->getBody(), btVector3(0,0,5), btVector3(8.25,0,-5), btVector3(0,1,0), btVector3(0,1,0));
	paddleHinge->setLimit(-M_PI, 0);
	paddleHinge->enableAngularMotor(true, 100, 100);

	sim->getDynamicsWorld()->addConstraint(paddleHinge, true);

	//alien
	alien->addToScene();
	alien->addToSimulator();

    //asteroid particle system
    ast1->addToScene();
    ast1->addToSimulator(sim->getDynamicsWorld());
}
//---------------------------------------------------------------------------
void GameScreen::update(const Ogre::FrameEvent &evt)
{
	sim->stepSimulation(evt.timeSinceLastFrame, 1, 1/60.0f);
}
//---------------------------------------------------------------------------
void GameScreen::updateClient(const Ogre::FrameEvent &evt, float * positions)
{
	//ship->setPosition(positions[0], positions[1], positions[2]);
	printf("set ship to %f, %f, %f\n", positions[0], positions[1], positions[2]);
	ship->setPosition(positions[0], positions[1], positions[2]);
	alien->setPosition(positions[3], positions[4], positions[5]);
	//paddle->setPosition(positions[6], positions[7], positions[8]);
	

}
//---------------------------------------------------------------------------
int GameScreen::getPositions(float * positions)
{
	Ogre::Vector3 pos = ship->getPos();
	positions[0] = pos.x;
	positions[1] = pos.y;
	positions[2] = pos.z;

	Ogre::Vector3 pos = alien->getPos();
	positions[3] = pos.x;
	positions[4] = pos.y;
	positions[5] = pos.z;
    
    //printf("positions[0] =%f\n", positions[0]);
    //printf("positions[1] =%f\n", positions[1]);
    //printf("positions[2] =%f\n", positions[2]);

	
	//paddle->getPosition(positions[3], positions[4], positions[5]);
	//alien->getPosition(positions[6], positions[7], positions[8]);

	/*int i;
	for(i = 0; i<12;i++){
		charPos[i] = '0' - i%9;
	}*/

	return 24;
}
//---------------------------------------------------------------------------
void GameScreen::injectKeyDown(const OIS::KeyEvent &arg)
{
	
	if (arg.key == OIS::KC_SPACE){
		if (motorRight)
			paddleHinge->enableAngularMotor(true, -100, 1000);
		else
			paddleHinge->enableAngularMotor(true, 100, 1000);
		motorRight = !motorRight;
		soundPlayer->playPaddleSwing();
	}
	if (arg.key == OIS::KC_M){
		soundPlayer->soundOff();
	}
	if (arg.key == OIS::KC_N){
		soundPlayer->soundOn();
	}
	

	ship->injectKeyDown(arg);
	paddle->injectKeyDown(arg);
	alien->injectKeyDown(arg);
}
//---------------------------------------------------------------------------
void GameScreen::injectKeyUp(const OIS::KeyEvent &arg)
{
	ship->injectKeyUp(arg);
	paddle->injectKeyUp(arg);
	alien->injectKeyUp(arg);
}
//---------------------------------------------------------------------------
void GameScreen::injectMouseMove(const OIS::MouseEvent &arg)
{
}
//---------------------------------------------------------------------------
void GameScreen::injectMouseDown(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}
//---------------------------------------------------------------------------
void GameScreen::injectMouseUp(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}
//---------------------------------------------------------------------------
void GameScreen::setDeetsPan(OgreBites::ParamsPanel*mDeetsPan)
{
	//mDetailsPanel = mDeetsPan;
	ship->setDeetsPan(mDeetsPan);
	paddle->setDeetsPan(mDeetsPan);
	alien->setDeetsPan(mDeetsPan);
}
//---------------------------------------------------------------------------