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
        int rejected;
        int accepted;
    protected:
        unsigned bucketSize;
        double transferSpeed; //packets per second
        std::vector<cMessage*> queue;
        simtime_t interval;
        simtime_t last_sent;

        virtual void initialize();
        virtual void handleMessage(cMessage* msg);
        virtual void finish() override;

    private:
        cMessage *leakingEvent;
        simsignal_t signalQSize;
        simsignal_t signalAccepted;
        simsignal_t signalRejected;
};
