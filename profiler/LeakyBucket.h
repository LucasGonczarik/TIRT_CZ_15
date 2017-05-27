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
    protected:
        int bucketSize;
        int rejected;
        int accepted;
        int transferSpeed; //packets per second
        //std::vector<cMessege*> queue;
        simtime_t interval;
        simtime_t last_sent;

        virtual void initialize() override;
        virtual void handleMessage(cMessage* msg) override;
        virtual void activity();

    private:
        simsignal_t signalQSize;
        simsignal_t signalAccepted;
        simsignal_t signalRejected;
};
