#include <cstdlib>
#include <time.h>
#include "Game.h"
#include "GameScreen.h"
#include <SdkCameraMan.h>

using namespace OgreBites;

//---------------------------------------------------------------------------
Game::Game(void)
{
    srand(time(0));
}
//---------------------------------------------------------------------------
Game::~Game(void)
{
}
//---------------------------------------------------------------------------
bool Game::configure(void)
{
    // Show the configuration dialog and initialise the system.
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg.
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise.
        // Here we choose to let the system create a default rendering window by passing 'true'.
        mWindow = mRoot->initialise(true, "Game Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//---------------------------------------------------------------------------
void Game::createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction  
    mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CameraNode");
    mCameraNode->attachObject(mCamera);
    mCameraNode->setPosition(Ogre::Vector3(0,0,0));

    mCamera->setPosition(Ogre::Vector3(0,50,-50));
    mCamera->lookAt(Ogre::Vector3(0,0,25));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
    //mCameraMan->setStyle(CS_MANUAL);
}
//---------------------------------------------------------------------------
void Game::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));    
}
//---------------------------------------------------------------------------
void Game::createFrameListener(void){
    BaseApplication::createFrameListener();
    gameScreen->setDeetsPan(mDetailsPanel);
}
//---------------------------------------------------------------------------
void Game::createScene(void)
{
    soundPlayer = new SoundPlayer();
    soundPlayer->startBgMusic();
    gameScreen = new GameScreen(mSceneMgr, mCameraNode, soundPlayer);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
    //game screen
    gameScreen->createScene();

    //sample stuff from old project
    //ground
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -750);
 
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);

    //ceiling
    Ogre::Plane plane2(Ogre::Vector3(0,-1,0), -750);
 
    Ogre::MeshManager::getSingleton().createPlane("ceiling", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane2, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
    Ogre::Entity* entCeiling = mSceneMgr->createEntity("CeilingEntity", "ceiling");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entCeiling);
 
    entCeiling->setMaterialName("Examples/Rockwall");
    entCeiling->setCastShadows(false);

    //left wall
    Ogre::Plane plane3(Ogre::Vector3(1,0,0), -750);
 
    Ogre::MeshManager::getSingleton().createPlane("lWall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane3, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
 
    Ogre::Entity* entLWall = mSceneMgr->createEntity("lWallEntity", "lWall");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entLWall);
 
    entLWall->setMaterialName("Examples/Rockwall");
    entLWall->setCastShadows(false);

    //right wall
    Ogre::Plane plane4(Ogre::Vector3(-1,0,0), -750);
 
    Ogre::MeshManager::getSingleton().createPlane("rWall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane4, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
 
    Ogre::Entity* entRWall = mSceneMgr->createEntity("rWallEntity", "rWall");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entRWall);
 
    entRWall->setMaterialName("Examples/Rockwall");
    entRWall->setCastShadows(false);

    //back wall
    Ogre::Plane plane5(Ogre::Vector3(0,0,1), -750);
 
    Ogre::MeshManager::getSingleton().createPlane("bWall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane5, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
 
    Ogre::Entity* entBWall = mSceneMgr->createEntity("bWallEntity", "bWall");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entBWall);
 
    entBWall->setMaterialName("Examples/Rockwall");
    entBWall->setCastShadows(false);

    //front wall
    Ogre::Plane plane6(Ogre::Vector3(0,0,-1), -750);
 
    Ogre::MeshManager::getSingleton().createPlane("fWall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane6, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
 
    Ogre::Entity* entFWall = mSceneMgr->createEntity("fWallEntity", "fWall");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entFWall);
 
    entFWall->setMaterialName("Examples/Rockwall");
    entFWall->setCastShadows(false);


    //Lights
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 500, 250));
 
    pointLight->setDiffuseColour(1.0, 1.0, 1.0);
    pointLight->setSpecularColour(1.0, 1.0, 1.0);

}
//---------------------------------------------------------------------------
void Game::destroyScene(void){
    delete gameScreen;
    delete soundPlayer;
    BaseApplication::destroyScene(); 
}
//---------------------------------------------------------------------------
bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt){
    gameScreen->update(evt);
    return BaseApplication::frameRenderingQueued(evt);
}
//---------------------------------------------------------------------------
bool Game::keyPressed(const OIS::KeyEvent &arg){
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    gameScreen->injectKeyDown(arg);

    return BaseApplication::keyPressed(arg);
}
//---------------------------------------------------------------------------
bool Game::keyReleased(const OIS::KeyEvent &arg)
{
    gameScreen->injectKeyUp(arg);
    mCameraMan->injectKeyUp(arg);
    return true;
}
//---------------------------------------------------------------------------
bool Game::mouseMoved(const OIS::MouseEvent &arg)
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
    gameScreen->injectMouseMove(arg);
    mCameraMan->injectMouseMove(arg);
    return true;
}
//---------------------------------------------------------------------------
bool Game::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    gameScreen->injectMouseDown(arg, id);
    mCameraMan->injectMouseDown(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool Game::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    gameScreen->injectMouseUp(arg, id);
    mCameraMan->injectMouseUp(arg, id);
    return true;
}
  //---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Game app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
