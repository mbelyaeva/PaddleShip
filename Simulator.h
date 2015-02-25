#include <Ogre.h>

class Simulator {
public:
	Simulator(void);
	~Simulator(void);
	void stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep);
	bool checkHit(int o);
};