#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* cameraNode)
{
	mSceneMgr = sceneMgr;
	ship = new Ship(sceneMgr, cameraNode);
	ast1 = new AsteroidSys(sceneMgr);
}
//---------------------------------------------------------------------------
GameScreen::~GameScreen(void)
{
}
//---------------------------------------------------------------------------
void GameScreen::createScene(void)
{
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