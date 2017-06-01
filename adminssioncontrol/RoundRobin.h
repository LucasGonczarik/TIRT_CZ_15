#ifndef ROUNDROBIN_H_
#define ROUNDROBIN_H_

#include <queue>
#include <map>
#include <omnetpp.h>
#include "../message/Message_m.h"

using namespace omnetpp;

class RoundRobin: public cSimpleModule {
    public:
        RoundRobin();
        virtual ~RoundRobin();
    protected:
            std::map<unsigned int, std::queue<Message*>> users;
            unsigned int lastServed;

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
            virtual unsigned int getNextUserToServed();

            //virtual void addMsgToUserQueue(Message* message);
};

#endif /* ROUNDROBIN_H_ */
