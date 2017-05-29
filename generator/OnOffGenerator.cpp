/*
 * OnOffGenerator.cpp
 *
 *  Created on: 28.05.2017
 *      Author: Piotr
 */

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
    paretoCondition = par("paretoCondition");
    BasicGenerator::initialize();
}

double OnOffGenerator::getDelay() {
    int delay = poisson(lambda);
    return delay;
}

void OnOffGenerator::checkIfIsOnModeActive() {
    //The condition can be different
    double paretoResult = pareto_shifted(a, b, 0, 0);
    if(paretoResult>paretoCondition){
        isOnModeActive = false;
    }
    else{
        isOnModeActive = true;
    }

}

bool OnOffGenerator::canSendMessage()
{
    checkIfIsOnModeActive();
    // Send only in "On" state
    return BasicGenerator::canSendMessage() && isOnModeActive;
}


