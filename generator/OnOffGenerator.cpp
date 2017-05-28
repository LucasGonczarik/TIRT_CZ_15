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
    BasicGenerator::initialize();
}

double OnOffGenerator::getDelay() {
    int delay = poisson(lambda);
    return delay;
}

bool OnOffGenerator::canSendMessage()
{
    // Send only in "On" state
    return BasicGenerator::canSendMessage() && isOnModeActive;
}


