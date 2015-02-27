#include "GameObject.h"

GameObject::GameObject(Ogre::SceneManager* sceneMgr) {
    mSceneMgr = sceneMgr;
    rootNode = mSceneMgr->getRootSceneNode();
}

GameObject::~GameObject(){
}

void GameObject::checkCollisions(bool check) {
    /*
    needsUpdates = check;
    if (!cCallBack && needsUpdates) {
        context = new CollisionContext();
        cCallBack = new BulletContactCallback(*body, *context);
    }
    */
}

void GameObject::addToSimulator(void) {
    /*
    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    updateTransform();
    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    if (mass != 0.0f) shape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
    rbInfo.m_restitution = restitution;
    rbInfo.m_friction = friction;
    body = new btRigidBody(rbInfo);
    body->setUserPointer(this);
    if (kinematic) {
        body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        body->setActivationState(DISABLE_DEACTIVATION);
    }
    simulator->addObject(this);
    */
}

void GameObject::update(void){
}