#include <cstdlib>
#include <time.h>
#include "Game.h"
#include "GameScreen.h"
#include <SdkCameraMan.h>

using namespace OgreBites;

//---------------------------------------------------------------------------
Game::Game(char *hostIP)
{
    srand(time(0));
    gameStarted = false;
    netMgr = NULL;
    clientFound = false;
    isServer = false;
    host = hostIP;
}
//---------------------------------------------------------------------------
Game::~Game(void)
{
    if(netMgr) delete netMgr;
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

    mCamera->setPosition(Ogre::Vector3(0,25,-40));
    mCamera->lookAt(Ogre::Vector3(0,0,25));
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
    gameScreen->setDeetsPan(mDetailsPanel);
}
//---------------------------------------------------------------------------
void Game::createScene(void)
{
    setUpSDL();

    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    
    guiRoot = wmgr.loadLayoutFromFile("main_menu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(guiRoot);
    
    CEGUI::Window *mainMenu = guiRoot->getChild("mainMenu");

    mainMenu->getChild("sPButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::startSinglePlayer, this));
    mainMenu->getChild("hostButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::startHosting, this));
    mainMenu->getChild("joinButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::joinGame, this));

    soundPlayer = new SoundPlayer();
    soundPlayer->startBgMusic();
    gameScreen = new GameScreen(mSceneMgr, mCameraNode, soundPlayer);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
    //game screen
    gameScreen->createScene();

    //Lights
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 500, -250));
 
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
    if(!gameStarted){
        if(isServer && !clientFound){
            if(netMgr->acceptClient()){
                clientFound = true;
                //start game
            }
        }
    }
    else
        gameScreen->update(evt); //render game

    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    return BaseApplication::frameRenderingQueued(evt);
}
//---------------------------------------------------------------------------
bool Game::keyPressed(const OIS::KeyEvent &arg){
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    gameScreen->injectKeyDown(arg);

    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);

    return BaseApplication::keyPressed(arg);
}
//---------------------------------------------------------------------------
bool Game::keyReleased(const OIS::KeyEvent &arg)
{
    gameScreen->injectKeyUp(arg);
    mCameraMan->injectKeyUp(arg);

    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);

    return true;
}
//---------------------------------------------------------------------------
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}
//---------------------------------------------------------------------------
bool Game::mouseMoved(const OIS::MouseEvent &arg)
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
    gameScreen->injectMouseMove(arg);
    mCameraMan->injectMouseMove(arg);

    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel)
        context.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    return true;
}
//---------------------------------------------------------------------------
bool Game::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    gameScreen->injectMouseDown(arg, id);
    mCameraMan->injectMouseDown(arg, id);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    return true;
}
//---------------------------------------------------------------------------
bool Game::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    gameScreen->injectMouseUp(arg, id);
    mCameraMan->injectMouseUp(arg, id);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    return true;
}
//---------------------------------------------------------------------------
bool Game::startSinglePlayer(const CEGUI::EventArgs &e)
{
    singlePlayer = true;
    gameStarted = true;
    guiRoot->setVisible(false);
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
    return true;
}
//---------------------------------------------------------------------------
void Game::setUpSDL(void)
{
    netMgr = new NetManager();
    netMgr->init();
    
}
//---------------------------------------------------------------------------
bool Game::startHosting(const CEGUI::EventArgs &e)
{
    singlePlayer = false;
    isServer = true;
    guiRoot->getChild("mainMenu/sPButton")->setVisible(false);
    guiRoot->getChild("mainMenu/hostButton")->setVisible(false);
    guiRoot->getChild("mainMenu/joinButton")->setVisible(false);
    guiRoot->getChild("mainMenu/infoBox")->setText("Waiting for another player...");
    netMgr->startServer();
    return true;
}
//---------------------------------------------------------------------------
bool Game::joinGame(const CEGUI::EventArgs &e)
{
    singlePlayer = false;
    isServer = false;

    if(!host){
        guiRoot->getChild("mainMenu/infoBox")->setText("Host must be provided as command line argument");
        return true;
    }

    std::cout << host << std::endl;

    netMgr->connectToServer(host);
    
    guiRoot->setVisible(false);
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
        char* host = argc > 1 ? argv[1] : NULL;
        Game app(host);

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
