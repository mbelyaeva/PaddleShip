#ifndef __Game_h_
#define __Game_h_

#include "BaseApplication.h"
#include "GameScreen.h"

//---------------------------------------------------------------------------

class Game : public BaseApplication
{
public:
  Game(void);
  virtual ~Game(void);

protected:
  virtual bool configure(void);
  virtual void createScene(void);
  virtual void createFrameListener(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
  virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

  virtual bool keyPressed(const OIS::KeyEvent &arg);
  virtual bool keyReleased(const OIS::KeyEvent &arg);
  virtual bool mouseMoved(const OIS::MouseEvent &arg);
  virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
  virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	GameScreen *gameScreen;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Game_h_

//---------------------------------------------------------------------------