#ifndef FCFS_H_
#define FCFS_H_

#include <queue>
#include <omnetpp.h>
#include "../message/Message_m.h"

using namespace omnetpp;

class FCFS: public cSimpleModule
{
    public:
        FCFS();
        virtual ~FCFS();
    protected:
        std::queue<Message*> buffer;
        unsigned int bufferCapacity;

        simtime_t messageHandlingTime;

        // metrics
        unsigned int acceptedCount;
        unsigned int rejectedCount;

        simsignal_t acceptedSignal;
        simsignal_t rejectedSignal;
        simsignal_t bufferSizeSignal;

        virtual void initialize();
        virtual void handleMessage(cMessage* msg);
};

#endif /* FCFS_H_ */
