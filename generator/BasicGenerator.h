/*
 * BasicGenerator.h
 *
 *  Created on: May 19, 2017
 *      Author: Marsel
 */

#ifndef GENERATOR_BASICGENERATOR_H_
#define GENERATOR_BASICGENERATOR_H_

#include <omnetpp.h>
#include "../message/Message_m.h"

using namespace omnetpp;

class BasicGenerator : public cSimpleModule {
    private:
        cMessage* event;
        simsignal_t eventSignal;

    protected:
        int sessionId;
        int messageId;

        virtual void initialize();
        virtual void handleMessage(cMessage* msg);

        virtual Message* generateMessage();
        virtual bool canSendMessage();
        virtual double getDelay() = 0;

    public:
        BasicGenerator();
        virtual ~BasicGenerator();
};

#endif /* GENERATOR_BASICGENERATOR_H_ */
