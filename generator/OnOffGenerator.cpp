#include "OnOffGenerator.h"

OnOffGenerator::OnOffGenerator() {
    // TODO Auto-generated constructor stub

}

OnOffGenerator::~OnOffGenerator() {
    // TODO Auto-generated destructor stub
}

Define_Module(OnOffGenerator);

void OnOffGenerator::initialize() {
    a = par("a");
    b = par("b");
    lambda = par("lambda");
    remainingPackets = par("remainingPackets");
    BasicGenerator::initialize();
}

double OnOffGenerator::getDelay() {
    if(isOnModeActive){
        int delay = poisson(lambda);
        return delay;
    }
    else{
        isOnModeActive = true;
        setNextPacketsLen();
        int delay= int(pareto_shifted(a,b,0,0));
        return delay;
    }
}

void OnOffGenerator::setNextPacketsLen() {
    remainingPackets = int(pareto_shifted(a,b,0,0) + 0.5);

    if(remainingPackets == 0) {
        remainingPackets = 1;
    }
}

void OnOffGenerator::checkIfIsOnModeActive() {
    if(remainingPackets == 0){
        isOnModeActive = false;
    }
    remainingPackets--;
}

bool OnOffGenerator::canSendMessage()
{
    checkIfIsOnModeActive();
    // Send only in "On" state
    return BasicGenerator::canSendMessage() && isOnModeActive;
}


