#include "GameScreen.h"

//---------------------------------------------------------------------------
GameScreen::GameScreen(Ogre::SceneManager* sceneMgr)
{
	mSceneMgr = sceneMgr;
}
//---------------------------------------------------------------------------
GameScreen::~GameScreen(void)
{
}
//---------------------------------------------------------------------------
void GameScreen::createScene(void){
	//ship
	entShip = mSceneMgr->createEntity("shipEntity", "sphere.mesh");
    entShip->setCastShadows(true);
    shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("shipNode", Ogre::Vector3(0, 0, 0));
    shipNode->attachObject(entShip);
    shipNode->setScale(Ogre::Vector3(1,1,1));
    //entShip->setMaterialName("Examples/Rockwall");

    //asteroid particle system
}
//---------------------------------------------------------------------------
void GameScreen::update(const Ogre::FrameEvent &evt){
}
//---------------------------------------------------------------------------