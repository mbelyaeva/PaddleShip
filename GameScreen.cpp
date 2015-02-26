#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr)
{
	mSceneMgr = sceneMgr;
	ship = new Ship(sceneMgr);
}
//---------------------------------------------------------------------------
GameScreen::~GameScreen(void)
{
}
//---------------------------------------------------------------------------
void GameScreen::createScene(void){
	//ship
	ship->addToScene();

    //asteroid particle system
}
//---------------------------------------------------------------------------
void GameScreen::update(const Ogre::FrameEvent &evt){
}
//---------------------------------------------------------------------------