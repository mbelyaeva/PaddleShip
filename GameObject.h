#ifndef __GameObject_h_
#define __GameObject_h_

#include <btBulletDynamicsCommon.h>
#include "OgreMotionState.h"
#include <Ogre.h>
#include "BulletContactCallback.h"

class Simulator;

class GameObject {
public:
    GameObject(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim);
    virtual ~GameObject(void);
    void updateTransform();
    virtual void addToSimulator();
    btRigidBody* getBody();
    virtual void update();
    BulletContactCallback* getCollisionCallback();


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
