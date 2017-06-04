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
            virtual void finish() override;
            virtual bool addTokenIfPossible();
    private:
        //signals tags
        const char* NEW_TOKEN_SIGNAL_TAG = "tokenGenerationEvent";
        const char* ACCEPTED_SIGNAL_TAG = "acceptedMessagesCount";
        const char* REJECTED_SIGNAL_TAG = "rejectedMessagesCount";

        double tokenGenerationInterval; //Rate at which tokens are being generated
        unsigned int maxTokenCount; //Maximum token count
        long rejectedMessagesCount = 0;
        long acceptedMessagesCount = 0;
        unsigned int currentTokenCount = 0;
        cMessage* tokenGenerationEvent;
        simsignal_t tokenGenerationEventSignal;
        simsignal_t signalAccepted;
        simsignal_t signalRejected;
    };

#endif /* PROFILER_TOKENBUCKET_H_ */
