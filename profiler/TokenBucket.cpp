/*
 * TokenBucket.cpp
 *
 *  Created on: 26.05.2017
 *      Author: dawhe
 */

#include "TokenBucket.h"

TokenBucket::TokenBucket() {
    tokenGenerationEvent = new cMessage(NEW_TOKEN_SIGNAL_TAG);
}

TokenBucket::~TokenBucket() {
    // TODO Auto-generated destructor stub
}

Define_Module(TokenBucket);

void TokenBucket::initialize() {
    //register
    tokenGenerationEventSignal = registerSignal(NEW_TOKEN_SIGNAL_TAG);
    //schedule token generation event;
    scheduleAt(simTime() + TOKEN_GENERATION_INTERVAL, tokenGenerationEvent);
}

void TokenBucket::handleMessage(cMessage* message) {
    //checks if event is token generation event or just a message from generator
    if (message == tokenGenerationEvent) {
        addTokenIfPossible();
        scheduleAt(simTime() + TOKEN_GENERATION_INTERVAL, tokenGenerationEvent);
    } else {
        //if there are tokens available send message and reduce current token count
        if (currentTokenCount > 0) {
            send(message, "out");
            currentTokenCount--;
        } else {
            rejectedMessagesCount++;
            EV << "No tokens! Message has been rejected!";
        }
    }
}

/**
 * @return
 * true -  if token has been added;
 * false -  if there was already maximum of available tokens
 */
bool TokenBucket::addTokenIfPossible() {
    if (currentTokenCount < MAX_TOKEN_COUNT) {
        currentTokenCount++;
        EV << "Token has been generated!";
        return true;
    } else {
        return false;
    }
}
