#include <vector>
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class LeakyBucket : public cSimpleModule
{
    public:
        LeakyBucket();
        virtual ~LeakyBucket();
        double rejected;
        double accepted;
        double packetLossRate;
    protected:
        double temporaryAcceptedInterval; //Time during which how many accepted messages were sent
        int temporaryAcceptedCount = 0;
        unsigned bucketSize;
        double transferSpeed; //packets per second
        std::vector<cMessage*> queue;
        simtime_t interval;
        simtime_t last_sent;

        virtual void initialize();
        virtual void handleMessage(cMessage* msg);
        virtual void finish();

    private:
        cMessage* temporaryAcceptedSendEvent;
        cMessage *leakingEvent;
        simsignal_t signalTemporaryAccepted;
        simsignal_t signalPacketLossRate;
        simsignal_t signalQSize;
        simsignal_t signalAccepted;
        simsignal_t signalRejected;
};
