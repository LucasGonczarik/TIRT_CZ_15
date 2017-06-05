/*
 * TokenBucket.cpp
 *
 *  Created on: 26.05.2017
 *      Author: dawhe
 */

#include "TokenBucket.h"

TokenBucket::TokenBucket() {
    tokenGenerationEvent = new cMessage(NEW_TOKEN_SIGNAL_TAG);
    temporaryAcceptedSendEvent = new cMessage(NEW_ACCEPTED_STAT_SIGNAL_TAG);
}

TokenBucket::~TokenBucket() {
    // TODO Auto-generated destructor stub
}

Define_Module(TokenBucket);

void TokenBucket::initialize() {
    //initialize parameters from submodule.TokenBucket.ned
    maxTokenCount = par("maxTokenCount");
    tokenGenerationInterval = par("tokenGenerationInterval");
    temporaryAcceptedInterval = par("temporaryAcceptedInterval");
    currentTokenCount = maxTokenCount;

    //register signals
    signalTemporaryAccepted = registerSignal(NEW_ACCEPTED_STAT_SIGNAL_TAG);
    tokenGenerationEventSignal = registerSignal(NEW_TOKEN_SIGNAL_TAG);
    signalPacketLossRate = registerSignal(PACKET_LOSS_RATE_SIGNAL_TAG);
    signalTemporaryAccepted = registerSignal(TEMPORARY_ACCEPTED_SIGNAL_TAG);
    signalTemporaryArrived = registerSignal(TEMPORARY_ARRIVED_SIGNAL_TAG);

    //schedule token generation event
    scheduleAt(simTime() + tokenGenerationInterval, tokenGenerationEvent);
    //schedule temporary accepted statistics event
    scheduleAt(simTime() + temporaryAcceptedInterval, temporaryAcceptedSendEvent);
}

void TokenBucket::handleMessage(cMessage* message) {
    //checks if event is token generation event, temporary accepted count statistics event or just a message from generator
    if (message == tokenGenerationEvent) {
        addTokenIfPossible();
        scheduleAt(simTime() + tokenGenerationInterval, tokenGenerationEvent);
    } else if (message == temporaryAcceptedSendEvent) {
        //send statistics (how many messages were accepted in time interval)
        EV << "Accepted messages count in last interval: " << temporaryAcceptedCount << endl;
        emit(signalTemporaryAccepted, temporaryAcceptedCount);
        emit(signalTemporaryArrived, temporaryArrivedCount);
        scheduleAt(simTime() + temporaryAcceptedInterval, temporaryAcceptedSendEvent);
        temporaryAcceptedCount = 0;
        temporaryArrivedCount = 0;
    } else {
        temporaryArrivedCount++;
        //if there are tokens available send message and reduce current token count
        if (currentTokenCount > 0) {
            send(message, "out");
            temporaryAcceptedCount++;
            acceptedMessagesCount++;
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
    if (currentTokenCount < maxTokenCount) {
        currentTokenCount++;
        EV << "Token has been generated!";
        return true;
    } else {
        return false;
    }
}

void TokenBucket::finish() {
    double packetLossRate = (rejectedMessagesCount/(rejectedMessagesCount + acceptedMessagesCount)) * 100;
    EV << "Packet loss rate: " << packetLossRate << endl;

    emit(signalPacketLossRate, packetLossRate);
}
