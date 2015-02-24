#include <cstdlib>
#include <time.h>
#include "Game.h"


#define BALL_RADIUS 50

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
void Game::createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,10,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
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
    
    Ogre::Real x = 50.0 + 450.0 * ((Ogre::Real) rand() / (RAND_MAX)); //random 50 to 500
    x *= -1 + 2 * (rand() % 2); //random -1 or 1
    Ogre::Real y = 50.0 + 450.0 * ((Ogre::Real) rand() / (RAND_MAX));
    y *= -1 + 2 * (rand() % 2);
    Ogre::Real z = 50.0 + 450.0 * ((Ogre::Real) rand() / (RAND_MAX));
    x *= -1 + 2 * (rand() % 2);
    ballVelocity = Ogre::Vector3(x, y, z);

}
//---------------------------------------------------------------------------
void Game::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
    //ball
    entBall = mSceneMgr->createEntity("ballEntity", "sphere.mesh");
    entBall->setCastShadows(true);
    ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ballNode", Ogre::Vector3(0, 0, 0));
    ballNode->attachObject(entBall);
    Ogre::Real scale = BALL_RADIUS/100.0;
    ballNode->setScale(Ogre::Vector3(scale,scale,scale));
    entBall->setMaterialName("Examples/Rockwall");

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
 
    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);

    Ogre::Light* pointLight2 = mSceneMgr->createLight("pointLight2");
    pointLight2->setType(Ogre::Light::LT_POINT);
    pointLight2->setPosition(Ogre::Vector3(0, 500, -100));
 
    pointLight2->setDiffuseColour(0.0, 0.5, 0.0);
    pointLight2->setSpecularColour(0.0, 0.5, 0.0);

    Ogre::Light* pointLight3 = mSceneMgr->createLight("pointLight3");
    pointLight3->setType(Ogre::Light::LT_POINT);
    pointLight3->setPosition(Ogre::Vector3(-100, 0, -700));
 
    pointLight3->setDiffuseColour(0.0, 0.0, 0.5);
    pointLight3->setSpecularColour(0.0, 0.0, 0.5);

 
    Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
 
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); 
 
    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
 
    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));
 
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
}
//---------------------------------------------------------------------------
bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt){
    ballNode -> translate(ballVelocity*evt.timeSinceLastFrame);
    const Ogre::Vector3 pos = ballNode -> getPosition();
    if (pos.x < -750 + BALL_RADIUS || pos.x > 750 - BALL_RADIUS) ballVelocity.x *= -1;
    if (pos.y < -750 + BALL_RADIUS || pos.y > 750 - BALL_RADIUS) ballVelocity.y *= -1;
    if (pos.z < -750 + BALL_RADIUS || pos.z > 750 - BALL_RADIUS) ballVelocity.z *= -1;
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
