/*
 * BasicGenerator.cpp
 *
 *  Created on: May 19, 2017
 *      Author: Marsel
 */

#include "BasicGenerator.h"

BasicGenerator::BasicGenerator() {
    // Create event message
       event = new cMessage("event");
       // Initialize...
       sessionId = intuniform(100, 999);
       messageId = 0;
}

BasicGenerator::~BasicGenerator() {
    cancelAndDelete(event);
}

void BasicGenerator::initialize() {
    // Initialize variables
    numSent = 0;
    WATCH(numSent);

    eventSignal = registerSignal("event");
    // Start sending messages after 1s
    scheduleAt(simTime() + exponential(1.0), event);
}

void BasicGenerator::handleMessage(cMessage* msg) {
    if (msg == event) {
        // Calculate delay
        simtime_t delay = getDelay();

        emit(eventSignal, delay);

        if (canSendMessage()) {
            // It's time to send message, so prepare new one and send
            bubble("SENDING new one!");
            send(generateMessage(), "out");
            numSent++;
        }

        // Send next message after delay
        scheduleAt(simTime() + delay, event);
    }
    else {
        // This should never happen, but for sure delete
        delete msg;
    }
}

Message* BasicGenerator::generateMessage() {
    char name[20];
    int src = getId();
    int dest = 31337;
    int priority = intrand(3) + 1; // low, normal, high
    messageId += 1;

    // Generate simple message name
    sprintf(name, "msg-%d", messageId);

    //Create new message
    Message* message = new Message(name);

    // Set properties
    message->setSessionID(sessionId);
    message->setMessageID(messageId);
    message->setSrc(src);
    message->setDst(dest);
    message->setSessionID(sessionId);
    message->setMessageID(messageId);
    message->setPriority(priority);
    message->setCreationTime(simTime());

    return message;
}

bool BasicGenerator::canSendMessage() {
    // Return false to cancel send
    return true;
}

void BasicGenerator::finish() {
    EV << "---------------------------" << endl;
    EV << "Sent: " << numSent << endl;
    EV << "---------------------------" << endl;
}
