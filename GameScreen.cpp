#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* cameraNode)
{
	mSceneMgr = sceneMgr;
	sim = new Simulator(sceneMgr);
	ship = new Ship("Ship", sceneMgr, sim, cameraNode);
	paddle = new Paddle("paddle", sceneMgr, sim, NULL); //change later
	ast1 = new AsteroidSys(sceneMgr, sim);
	
}
//---------------------------------------------------------------------------
GameScreen::~GameScreen(void)
{
	delete ship;
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

	//paddleHinge = new btHingeConstraint(*ship->getBody(), *paddle->getBody(), btVector3(0,0,-5), btVector3(-8.25f, 0.0f, 10.0f), btVector3(0,1,0), btVector3(0,1,0));
	//paddleHinge->setDbgDrawSize(btScalar(50.f));
	//sim->getDynamicsWorld()->addConstraint(paddleHinge, true);

    //asteroid particle system
    ast1->addToScene();
    ast1->addToSimulator(sim->getDynamicsWorld());
}
//---------------------------------------------------------------------------
void GameScreen::update(const Ogre::FrameEvent &evt)
{
	sim->stepSimulation(evt.timeSinceLastFrame, 1, 1/60.0f);
	//ship->update();
	//ast1->update();
}
//---------------------------------------------------------------------------
void GameScreen::injectKeyDown(const OIS::KeyEvent &arg)
{
	ship->injectKeyDown(arg);
	paddle->injectKeyDown(arg);
}
//---------------------------------------------------------------------------
void GameScreen::injectKeyUp(const OIS::KeyEvent &arg)
{
	ship->injectKeyUp(arg);
	paddle->injectKeyUp(arg);
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