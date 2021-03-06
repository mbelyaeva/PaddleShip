#ifndef __OgreMotionState_h_
#define __OgreMotionState_h_

#include <btBulletDynamicsCommon.h>
#include <Ogre.h>

class OgreMotionState : public btMotionState {
protected:
	Ogre::SceneNode* mVisibleobj;
	btTransform mPos1;
public:
	OgreMotionState(const btTransform& initialpos, Ogre::SceneNode* node) {
		mVisibleobj = node;
		mPos1 = initialpos;
	}
	virtual ~OgreMotionState() {}
	
	void setNode(Ogre::SceneNode* node) {
		mVisibleobj = node;
	}
	void updateTransform(btTransform& newpos) {
		mPos1 = newpos;
	}
	virtual void getWorldTransform(btTransform& worldTrans) const {
		worldTrans = mPos1;
	}
	virtual void setWorldTransform(const btTransform& worldTrans) {
		if(NULL == mVisibleobj)
			return; // silently return before we set a node
		btQuaternion rot = worldTrans.getRotation();
		mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
		btVector3 pos = worldTrans.getOrigin();
		mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
	}
};

//---------------------------------------------------------------------------

#endif // #ifndef __OgreMotionState_h_

//---------------------------------------------------------------------------