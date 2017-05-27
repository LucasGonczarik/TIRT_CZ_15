#ifndef RED_H_
#define RED_H_

#include <vector>
#include <omnetpp.h>
#include "../message/Message_m.h"

using namespace omnetpp;

class RED: public cSimpleModule
{
    public:
        RED();
        virtual ~RED();
    protected:
        std::vector<Message*> buffer;
        int bufferSize;
        int minBuffer;
        int maxBuffer;
        int mean;

        simtime_t messageHandlingTime;
        unsigned long long messageNumber;

        // metrics
        unsigned int acceptedCount;
        unsigned int rejectedCount;

        simsignal_t acceptedSignal;
        simsignal_t rejectedSignal;
        simsignal_t bufferSizeSignal;

        virtual void initialize();

        virtual bool check(Message* message);
        virtual void handleMessage(cMessage* msg);
};

#endif /* RED_H_ */
