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
  virtual void createScene(void);
  virtual void createFrameListener(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
	GameScreen *gameScreen;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Game_h_

//---------------------------------------------------------------------------