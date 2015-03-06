#include "Simulator.h"

Simulator::Simulator(Ogre::SceneManager* mgr)
{
    ///collision configuration contains default setup for memory, collision setup.
    collisionConfiguration = new btDefaultCollisionConfiguration();
    ///use the default collision dispatcher. For parallel processing you can use a different dispatcher
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    overlappingPairCache = new btDbvtBroadphase();
    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, 0, 0)); //we're in space
    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    sceneMgr = mgr;
    mDebugDrawer = new CDebugDraw(mgr, dynamicsWorld);
    dynamicsWorld->setDebugDrawer(mDebugDrawer);
}

Simulator::~Simulator()
{
}

void Simulator::addObject (GameObject* o)
{
    objList.push_back(o);
    // use default collision group/mask values (dynamic/kinematic/static)
    dynamicsWorld->addRigidBody(o->getBody());
}

void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep)
{
    dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
    for (unsigned int i = 0; i < objList.size(); i++)
        objList[i]->update();
    mDebugDrawer->Update();
}

btDiscreteDynamicsWorld* Simulator::getDynamicsWorld() {
    return dynamicsWorld;
}

/*void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep)
{
    for (int i = 0; i != objList.size(); i++) idList[i] = 0;
    dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
    for (unsigned int i = 0; i < objList.size(); i++)
        if (objList[i].gObject->doUpdates()) objList[i].gObject->update(elapsedTime);
}*/

/*bool Simulator::checkHit(int o)
{
    for (int i = idList[o]; i < objList.size(); i++) {
        if (i != o) {
            objList[o].gObject->context->hit = false;
            dynamicsWorld->contactPairTest(objList[o].gObject->getBody(), objList[i].gObject->getBody(), objList[o]);
            if (objList[o].gObject->context->hit) {
                idList[o] = ++i;
                return true;
            }
        }
    }
    return false;
}*/
