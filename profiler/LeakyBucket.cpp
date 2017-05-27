/*
 * LeakyBucket.cpp
 *
 *  Created on: 26.05.2017
 *      Author: seremonik
 */

#include "LeakyBucket.h"

LeakyBucket::LeakyBucket()
{
    last_sent = 0.0;
    rejected = 0;
    accepted = 0;
}

LeakyBucket::~LeakyBucket()
{

}

Define_Module(LeakyBucket);

void LeakyBucket::initialize()
{
    rejected = 0;
    last_sent = 0.0;
    accepted = 0;
    bucketSize = par("bucketSize");
    transferSpeed = par("transferSpeed").doubleValue();
    EV << transferSpeed<<endl;
    //transferSpeed = 1.0 / transferSpeed;
    leakingEvent = new cMessage("leakingEvent");
    EV << transferSpeed<<endl;
    scheduleAt(simTime(), leakingEvent);
    //interval= par("interval");
    //signalQSize = registerSignal("qsize"); //todo
    //signalAccepted = registerSignal("accepted"); //todo
    //signalRejected = registerSignal("rejected"); //todo
}

/*
void LeakyBucket::activity()
{

    while(true){
        EV<<"LeakyQsize: "<<queue_size<<" simTime: "<< simTime() <<" last_sent: "<< last_sent <<std::endl;
        cMessage* msg = receive();
        if(msg != NULL && (queue_size < max_queue_size)){
            Packet* packet = check_and_cast<Packet*>(msg);
            queue.push_back(packet);
            queued++;
        }else rejected++;

        if((simTime()-last_sent) > interval){
            Packet* packet = queue.front();
            queue.erase(queue.begin());
            send(packet, "out");

            last_sent = simTime();
            sent++;
        }

        queue_size = queue.size();

        emit(signalQSize, queue_size);
    }
}*/
void LeakyBucket::handleMessage(cMessage* msg)
{
    if(msg == leakingEvent)
    {
        if(!queue.empty())
        {
            queue.erase(queue.begin());
            accepted++;
            EV<<"accepted!";
        }

        scheduleAt(simTime() + transferSpeed, leakingEvent);
    }

    else
    {
        EV<<"wyslano!";
        if(queue.size() >= bucketSize)
        {
            EV<<"rejected!";
            rejected++;
        }
        else
        {
            queue.push_back(msg);
        }
        delete msg;
    }

}

