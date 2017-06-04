/*
 * LeakyBucket.cpp
 *
 *  Created on: 26.05.2017
 *      Author: seremonik
 */

#include "LeakyBucket.h"

LeakyBucket::LeakyBucket()
{
    rejected = 0;
    last_sent = 0.0;
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
    leakingEvent = new cMessage("leakingEvent");
    EV << transferSpeed<<endl;
    signalAccepted = registerSignal("accepted"); //todo
    signalRejected = registerSignal("rejected"); //todo
    signalQSize = registerSignal("qsize"); //todo
    scheduleAt(simTime(), leakingEvent);

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
            accepted++;
            EV<<"Przes³ano pakiet dalej! ilosc pakietow w kolejce: "<<queue.size()<<"/"<<bucketSize<<endl;
        }

        scheduleAt(simTime() + transferSpeed, leakingEvent);
    }

    else
    {
        if(queue.size() >= bucketSize)
        {
            EV<<"odrzucono pakiet! ilosc pakietow w kolejce: "<<queue.size()<<"/"<<bucketSize<<endl;
            rejected++;
        }
        else
        {
            queue.push_back(msg);
            EV<<"zakolejkowano, ilosc pakietow w kolejce: "<<queue.size()<<"/"<<bucketSize<<endl;
        }
        delete msg;
    }

    emit(signalAccepted, accepted);
    emit(signalRejected, rejected);
    emit(signalQSize, (int)queue.size());
}

void LeakyBucket::finish() {
    EV << "---------------------------" << endl;
    EV << "Accepted: " << accepted << endl;
    EV << "Rejected: " << rejected << endl;
    EV << "---------------------------" << endl;
}

