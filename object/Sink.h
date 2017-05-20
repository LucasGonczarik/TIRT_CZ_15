/*
 * Sink.h
 *
 *  Created on: May 20, 2017
 *      Author: Marsel
 */

#ifndef OBJECT_SINK_H_
#define OBJECT_SINK_H_

#include <map>
#include <omnetpp.h>
#include "../message/Message_m.h"

using namespace omnetpp;

typedef std::map<int, cLongHistogram*> PriorityStatsMap;

class Sink : public cSimpleModule
{
    private:
        int packet_count;
        simsignal_t eventSignal;
        PriorityStatsMap priorityStats;

        // We might need this later
        cLongHistogram* createHistogram(int priority);
        cLongHistogram* getHistogram(int priority);
    protected:
        virtual void initialize();
        virtual void finish();
        virtual void handleMessage(cMessage* msg);
    public:
        Sink();
        virtual ~Sink();
};

#endif /* OBJECT_SINK_H_ */
