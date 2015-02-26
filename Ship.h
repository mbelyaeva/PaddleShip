#ifndef __Ship_h_
#define __Ship_h_

#include "GameObject.h"

//---------------------------------------------------------------------------

class Ship: public GameObject 
{
public:
	Ship(Ogre::SceneManager* sceneMgr);
	~Ship(void);
	void addToScene(void);
	void update(void);

protected:
	Ogre::Entity *entShip;
	Ogre::SceneNode *shipNode;
	Ogre::Vector3 velocity;
	Ogre::Vector3 position;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Ship_h_

//---------------------------------------------------------------------------