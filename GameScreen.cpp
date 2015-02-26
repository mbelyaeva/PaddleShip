#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr)
{
	mSceneMgr = sceneMgr;
	ship = new Ship(sceneMgr);
	ast1 = new Asteroid(sceneMgr);
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
    ast1->addToScene();
}
//---------------------------------------------------------------------------
void GameScreen::update(const Ogre::FrameEvent &evt){
}
//---------------------------------------------------------------------------