/*
 * TokenBucket.cpp
 *
 *  Created on: 26.05.2017
 *      Author: dawhe
 */

#include "TokenBucket.h"

TokenBucket::TokenBucket() {
    // TODO Auto-generated constructor stub

}

TokenBucket::~TokenBucket() {
    // TODO Auto-generated destructor stub
}

Define_Module(TokenBucket);

void TokenBucket::initialize() {

}

void TokenBucket::handleMessage(cMessage* message) {
    send(message, "out");
}
