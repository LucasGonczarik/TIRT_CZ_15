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
    temporaryAcceptedInterval = par("temporaryAcceptedInterval");
    bucketSize = par("bucketSize");
    transferSpeed = par("transferSpeed").doubleValue();
    EV << transferSpeed<<endl;
    leakingEvent = new cMessage("leakingEvent");
    temporaryAcceptedSendEvent = new cMessage("acceptedStatSignalEvent");
    signalTemporaryAccepted = registerSignal("temporaryAcceptedCount");
    signalAccepted = registerSignal("accepted"); //todo
    signalRejected = registerSignal("rejected"); //todo
    signalPacketLossRate = registerSignal("packetLossRate");
    signalQSize = registerSignal("qsize"); //todo
    scheduleAt(simTime(), leakingEvent);
    scheduleAt(simTime() + temporaryAcceptedInterval, temporaryAcceptedSendEvent);
    //interval= par("interval");
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
            temporaryAcceptedCount++;
            accepted++;
            EV<<"Przes³ano pakiet dalej! ilosc pakietów w kolejce: "<<queue.size()<<"/"<<bucketSize<<endl;
        }

        scheduleAt(simTime() + transferSpeed, leakingEvent);
    }
    else if (msg == temporaryAcceptedSendEvent)
    {
        //send statistics (how many messages were accepted in time interval)
        EV << "Accepted messages count in last interval: " << temporaryAcceptedCount << endl;
        emit(signalTemporaryAccepted, temporaryAcceptedCount);
        emit(signalQSize, (int)queue.size());
        scheduleAt(simTime() + temporaryAcceptedInterval, temporaryAcceptedSendEvent);
        temporaryAcceptedCount = 0;
    }
    else
    {
        if(queue.size() >= bucketSize)
        {
            EV<<"odrzucono pakiet! ilosc pakietów w kolejce: "<<queue.size()<<"/"<<bucketSize<<endl;
            rejected++;
        }
        else
        {
            queue.push_back(msg);
            EV<<"zakolejkowano, ilosc pakietów w kolejce: "<<queue.size()<<"/"<<bucketSize<<endl;
        }
        delete msg;
    }

}

void LeakyBucket::finish() {
    double packetLossRate = (rejected/(rejected + accepted)) * 100;
    EV << "Packet loss rate: " << packetLossRate << endl;

    emit(signalPacketLossRate, packetLossRate);
    //emit(signalAccepted, accepted);
    //emit(signalRejected, rejected);
}


