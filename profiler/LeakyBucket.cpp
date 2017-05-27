/*
 * LeakyBucket.cpp
 *
 *  Created on: 26.05.2017
 *      Author: seremonik
 */

#include "LeakyBucket.h"

Define_Module(LeakyBucket);

LeakyBucket::LeakyBucket():cSimpleModule(1024)
{
    last_sent = 0.0;
    rejected = 0;
}

LeakyBucket::~LeakyBucket()
{

}

void LeakyBucket::initialize()
{
    bucketSize = par("bucketSize");
    transferSpeed = par("transferSpeed");
    //interval= par("interval");
    //signalQSize = registerSignal("qsize"); //todo
    //signalAccepted = registerSignal("accepted"); //todo
    //signalRejected = registerSignal("rejected"); //todo
}

void LeakyBucket::activity()
{
    /*
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
        emit(signalAccepted, queued);
        emit(signalRejected, rejected);
    }*/
}

void LeakyBucket::handleMessage(cMessage *msg)
{
    EV << "Got message";
}
