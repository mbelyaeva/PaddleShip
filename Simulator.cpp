#include "Simulator.h"

void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep) {
    /*for (int i = 0; i != objList.size(); i++) idList[i] = 0;
    dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
    for (unsigned int i = 0; i < objList.size(); i++)
        if (objList[i].gObject->doUpdates()) objList[i].gObject->update(elapsedTime);*/
}

bool Simulator::checkHit(int o) {
    /*for (int i = idList[o]; i < objList.size(); i++) {
        if (i != o) {
            objList[o].gObject->context->hit = false;
            dynamicsWorld->contactPairTest(objList[o].gObject->getBody(), objList[i].gObject->getBody(), objList[o]);
            if (objList[o].gObject->context->hit) {
                idList[o] = ++i;
                return true;
            }
        }
    }
    return false;*/
}