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
        const unsigned int MAX_TOKEN_COUNT = 5; //Maximum token count
        const simtime_t TOKEN_GENERATION_INTERVAL = 20; //Rate at which tokens are being generated
        const char* NEW_TOKEN_SIGNAL_TAG = "tokenGenerationEvent";

        unsigned int rejectedMessagesCount = 0;
        unsigned int currentTokenCount = MAX_TOKEN_COUNT;
        cMessage* tokenGenerationEvent;
        simsignal_t tokenGenerationEventSignal;
    };

#endif /* PROFILER_TOKENBUCKET_H_ */
