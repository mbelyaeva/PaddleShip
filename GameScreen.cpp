#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* cameraNode)
{
	mSceneMgr = sceneMgr;
	sim = new Simulator();
	ship = new Ship("Ship", sceneMgr, sim, cameraNode);
	ast1 = new AsteroidSys(sceneMgr, sim);
	
}
//---------------------------------------------------------------------------
GameScreen::~GameScreen(void)
{
	delete ship;
	delete ast1;
	delete sim;
}
//---------------------------------------------------------------------------
void GameScreen::createScene(void)
{
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
	
	//ship
	ship->addToScene();
	
    //asteroid particle system
    ast1->addToScene();
}
//---------------------------------------------------------------------------
void GameScreen::update(const Ogre::FrameEvent &evt)
{
	ship->update();
	ast1->update();
}
//---------------------------------------------------------------------------
void GameScreen::injectKeyDown(const OIS::KeyEvent &arg)
{
	ship->injectKeyDown(arg);
}
//---------------------------------------------------------------------------
void GameScreen::injectKeyUp(const OIS::KeyEvent &arg)
{
	ship->injectKeyUp(arg);
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