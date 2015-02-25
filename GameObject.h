#ifndef __GameObject_h_
#define __GameObject_h_

#include <Ogre.h>
#include "BulletContactCallback.h"
#include "Simulator.h"
class OgreMotionState;

class GameObject {
public:
    GameObject(void);
    virtual ~GameObject(void);
    void checkCollisions(bool check);
    void addToSimulator(void);
    virtual void update(void);

protected:
    Ogre::String name;
    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* rootNode;
    Ogre::Entity* geom;
    OgreMotionState* motionState;

    Simulator* simulator;
    btCollisionShape* shape;
    btRigidBody* body;
    btTransform tr;
    btVector3 inertia;

    btScalar mass;
    btScalar restitution;
    btScalar friction;
    bool kinematic;
    bool needsUpdates;

    CollisionContext* context;
    BulletContactCallback* cCallBack;

};

//---------------------------------------------------------------------------

#endif // #ifndef __GameScreen_h_

//---------------------------------------------------------------------------