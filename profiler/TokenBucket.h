/*
 * TokenBucket.h
 *
 *  Created on: 26.05.2017
 *      Author: dawhe
 */

#ifndef PROFILER_TOKENBUCKET_H_
#define PROFILER_TOKENBUCKET_H_

#include <omnetpp.h>

using namespace omnetpp;

class TokenBucket: public cSimpleModule {
    public:
        TokenBucket();
        virtual ~TokenBucket();
    protected:
            virtual void initialize();
            virtual void handleMessage(cMessage* msg);
            virtual bool addTokenIfPossible();
    private:
        const char* NEW_TOKEN_SIGNAL_TAG = "tokenGenerationEvent";

        double tokenGenerationInterval; //Rate at which tokens are being generated
        unsigned int maxTokenCount; //Maximum token count
        unsigned int rejectedMessagesCount = 0;
        unsigned int currentTokenCount = 0;
        cMessage* tokenGenerationEvent;
        simsignal_t tokenGenerationEventSignal;
    };

#endif /* PROFILER_TOKENBUCKET_H_ */
