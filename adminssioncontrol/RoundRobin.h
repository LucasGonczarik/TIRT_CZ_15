#ifndef ROUNDROBIN_H_
#define ROUNDROBIN_H_


#include <algorithm>
#include<functional>
#include <vector>
#include <map>
#include <omnetpp.h>
#include "../message/Message_m.h"
//#include <deque>
//#include <queue>

using namespace omnetpp;

class RoundRobin: public cSimpleModule {
    public:
        RoundRobin();
        virtual ~RoundRobin();
    protected:
            std::map<unsigned int, std::vector<Message*>> users;
            std::vector<std::vector<Message*>*> usersOrdered2Served;

            std::vector<Message*> buffer;
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
            virtual Message* getNextMessageToServed();

            virtual void showVector(std::vector<Message*> vector);
            virtual void showVectorOfVectors(std::vector<std::vector<Message*>*> vector);
            virtual void  showInfoAboutVariables();
};

#endif /* ROUNDROBIN_H_ */
