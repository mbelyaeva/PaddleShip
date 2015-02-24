#ifndef __Game_h_
#define __Game_h_

#include "BaseApplication.h"

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
	Ogre::Vector3 ballVelocity;
	Ogre::Entity *entBall;
	Ogre::SceneNode *ballNode;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Game_h_

//---------------------------------------------------------------------------