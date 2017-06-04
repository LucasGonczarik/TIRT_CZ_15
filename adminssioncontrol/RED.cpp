#include "RED.h"

RED::RED()
{
    bufferSize = 20;
    minBuffer = 3;
    maxBuffer = 17;
    mean = 0;

    messageNumber = 0;

    acceptedCount = 0;
    rejectedCount = 0;
}

RED::~RED()
{
}

Define_Module(RED);

void RED::initialize()
{
    messageHandlingTime = par("messageHandlingTime");
    acceptedSignal = registerSignal("acceptedSignal");
    rejectedSignal = registerSignal("rejectedSignal");
    bufferSizeSignal = registerSignal("bufferSizeSignal");
}

void RED::handleMessage(cMessage* msg)
{
    Message* message = check_and_cast<Message*>(msg);
    messageNumber++;
    mean = (mean + buffer.size()) / 2;

    if (buffer.size() == bufferSize) {
        mean = bufferSize;
    }

    if (!msg->isSelfMessage()) {
        if (this->check(message)) {
            acceptedCount++;;
            buffer.push_back(message);
            scheduleAt(simTime() + messageHandlingTime, message);
            EV << ";" <<  (int) simTime().dbl() << ";accepted; " << buffer.size() << ";" << rejectedCount << ";" << acceptedCount << std::endl;
        } else {
            rejectedCount++;
            EV << ";" <<  (int) simTime().dbl() << ";rejected; " << buffer.size() << ";" << rejectedCount << ";" << acceptedCount << std::endl;
        }
    } else {
        Message* message = buffer.front();
        buffer.erase(buffer.begin());
        send(message, "out");
    }

    emit(bufferSizeSignal, (long) buffer.size());
    emit(acceptedSignal, (long) acceptedCount);
    emit(rejectedSignal, (long) rejectedCount);
}

bool RED::check(Message* message) {
    if (mean <= minBuffer) {
        return true;
    }

    if (mean >= maxBuffer) {
        return false;
    }

    int probability = ((1 / (maxBuffer - minBuffer)) * mean - minBuffer / (maxBuffer - minBuffer)) * 100;

    return rand() % 101 < (100 - probability);
}
