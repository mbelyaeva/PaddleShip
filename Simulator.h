#ifndef __Simulator_h_
#define __Simulator_h_

#include <Ogre.h>
#include <vector>
//#include "GameObject.h"

using std::vector;

class Simulator {
public:
	Simulator(void);
	~Simulator(void);
	void stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep);
	bool checkHit(int o);

protected:
	//vector<GameObject> objList;
	//btDynamicsWorld
};

//---------------------------------------------------------------------------

#endif // #ifndef __Ship_h_

//---------------------------------------------------------------------------