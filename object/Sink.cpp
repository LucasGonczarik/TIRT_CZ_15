/*
 * Sink.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Marsel
 */

#include "../object/Sink.h"

Sink::Sink() {
    // TODO Auto-generated constructor stub

}

Sink::~Sink() {
    // TODO Auto-generated destructor stub
}

// register module class with OMNeT++
Define_Module(Sink);

void Sink::initialize() {
    eventSignal = registerSignal("event");
    packet_count = 0;
}

void Sink::finish() {
    char name[25];
    for (PriorityStatsMap::iterator i = priorityStats.begin(); i != priorityStats.end(); i++) {
        sprintf(name, "priority-%d", i->first);
        i->second->recordAs(name);
    }
}

void Sink::handleMessage(cMessage* msg) {
    double currentTime = simTime().dbl();
    Message* message = check_and_cast<Message*>(msg);
    double delay = currentTime - message->getCreationTime();
    int priority = message->getPriority();
    cLongHistogram* stat = getHistogram(priority);

    EV << "Send time: " << delay << endl;
    emit(eventSignal, delay);
    stat->collect(delay);

    packet_count++;

    delete msg;
}

cLongHistogram* Sink::createHistogram(int priority) {
    cLongHistogram* stat = new cLongHistogram();
    priorityStats[priority] = stat;
    return stat;
}

cLongHistogram* Sink::getHistogram(int priority) {
  return priorityStats.count(priority) ? priorityStats[priority] : createHistogram(priority);
}
