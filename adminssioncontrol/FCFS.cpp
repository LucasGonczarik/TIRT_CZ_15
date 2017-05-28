#include "FCFS.h"

FCFS::FCFS()
{
    acceptedCount = 0;
    rejectedCount = 0;
}

FCFS::~FCFS()
{
}

Define_Module(FCFS);

void FCFS::initialize()
{
    bufferCapacity = par("bufferCapacity");
    messageHandlingTime = par("messageHandlingTime");
    acceptedSignal = registerSignal("acceptedSignal");
    rejectedSignal = registerSignal("rejectedSignal");
    bufferSizeSignal = registerSignal("bufferSizeSignal");
}

void FCFS::handleMessage(cMessage* msg)
{
    if (msg != nullptr) {
        if (!msg->isSelfMessage()) {
            Message* message = check_and_cast<Message*>(msg);
            if (buffer.size() < bufferCapacity) {
                ++acceptedCount;
                buffer.push(message);
                scheduleAt(simTime() + messageHandlingTime, message);
            } else {
                ++rejectedCount;
            }
        } else {
            Message* message = buffer.front();
            buffer.pop();
            send(message, "out");
            EV << buffer.size() << std::endl;
        }
    }

    EV << "BufferSize: " << buffer.size() << " Rejected: " << rejectedCount << " Accepted: " << acceptedCount << std::endl;

    emit(bufferSizeSignal, (long) buffer.size());
    emit(acceptedSignal, (long) acceptedCount);
    emit(rejectedSignal, (long) rejectedCount);
}
