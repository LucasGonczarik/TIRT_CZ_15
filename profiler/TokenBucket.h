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
    private:
        const simtime_t TOKEN_INTERVAL = 2;
    };

#endif /* PROFILER_TOKENBUCKET_H_ */
