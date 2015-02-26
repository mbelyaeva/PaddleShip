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
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

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
    mCamera->setPosition(Ogre::Vector3(0,750,750));
    mCamera->lookAt(Ogre::Vector3(0,0,-250));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
    mCameraMan->setStyle(CS_MANUAL);
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
}
//---------------------------------------------------------------------------
void Game::createScene(void)
{
    gameScreen = new GameScreen(mSceneMgr);
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
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));
 
    pointLight->setDiffuseColour(1.0, 1.0, 1.0);
    pointLight->setSpecularColour(1.0, 1.0, 1.0);

}
//---------------------------------------------------------------------------
void Game::destroyScene(void){
    delete gameScreen;
    BaseApplication::destroyScene(); 
}
//---------------------------------------------------------------------------
bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt){
    gameScreen->update(evt);
    return BaseApplication::frameRenderingQueued(evt);
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
