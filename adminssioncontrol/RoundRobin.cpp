#include "RoundRobin.h"

RoundRobin::RoundRobin() {
    acceptedCount = 0;
    rejectedCount = 0;
}

RoundRobin::~RoundRobin() { }

Define_Module(RoundRobin);

void RoundRobin::initialize()
{
    bufferCapacity = par("bufferCapacity");
    messageHandlingTime = par("messageHandlingTime");
    acceptedSignal = registerSignal("acceptedSignal");
    rejectedSignal = registerSignal("rejectedSignal");
    bufferSizeSignal = registerSignal("bufferSizeSignal");
}

void RoundRobin::handleMessage(cMessage* msg)
{
   if (msg != nullptr) {
       if (!msg->isSelfMessage()) {
           Message* message = check_and_cast<Message*>(msg);
           if (buffer.size() < bufferCapacity) {
               users[message->getSrc()].push(message);
               ++acceptedCount;
               buffer.push(message);
               scheduleAt(simTime() + messageHandlingTime, message);
           } else {
               ++rejectedCount;
           }
           EV << "Source: " << message->getSrc() << std::endl;
       } else {
          unsigned int nextUser2ServeKey = getNextUserToServed();
          std::queue<Message*> userQueue = users.find(nextUser2ServeKey)->second;
          while(userQueue.empty())
          {
                unsigned int old = nextUser2ServeKey;
                lastServed = nextUser2ServeKey;
                nextUser2ServeKey = getNextUserToServed();
                users.erase(old);
                userQueue = users.find(nextUser2ServeKey)->second;
          }

          Message* sendMessage = users.find(nextUser2ServeKey)->second.front(); // buffer.push(sendMessage);
          users.find(nextUser2ServeKey)->second.pop();
          lastServed = nextUser2ServeKey;  //  Message* message = buffer.front();
          buffer.pop();
          send(sendMessage, "out"); //z jakiegos powodu wsykakuje error podczas symulacji.
          EV << "SOURCE OUT: " << sendMessage->getSrc() << ", buffer size: " << buffer.size() << std::endl;
       }
   }

    EV  <<"BufferSize: " << buffer.size() << " Rejected: " << rejectedCount << " Accepted: " << acceptedCount << std::endl;

    emit(bufferSizeSignal, (long) buffer.size());
    emit(acceptedSignal, (long) acceptedCount);
    emit(rejectedSignal, (long) rejectedCount);
}

unsigned int RoundRobin::getNextUserToServed()//zastanowic sie czy dobrze, bo niestety mapa uklada sie w kolejnosci rosnacej kluczy.
{
    std::map<unsigned int, std::queue<Message*>>::iterator  outer = users.begin();
    while(outer->first != lastServed && outer != users.end())
    {
        ++outer;
    }

    if(outer == users.end()) outer = users.begin();
    else
    {
        outer++;
        if(outer == users.end()) outer = users.begin();
    }
    return outer->first;

}









/*
 * Generalnie pomysl jest taki:
 *  1.Przys³an¹ wiadomoœæ dodaj do kolejki usera.
 *  2.Daj  kolejke usera, który jako kolejny zosta³ dodany do "mapy"
 *  3. Powtarzaj 2. Dopuki kolejka jest pusta
 *  4. Wez pierwsza wiadomosc z kolejki usera i daj ja do bufor.
 *  5. Usun pobrana wiadomosc z kolejki usera.
 *  6. lastServed = Klucz, do kolejki z ktorej zosta³a dodana do bufora pobrana wiadomosc.
 */




/* std::map<unsigned int, std::queue<Message*>>::iterator it= users.find(message->getSrc());
               if(it == users.end())
               {
                   EV << "QUeue for source: " << message->getSrc() <<" not found!!!" << std::endl;
                   users[message->getSrc()].push(message); //TODO pomyslec czy nie styknie tylko to
               }
               else
               {
                   it->second.push(message);
               } */

/*unsigned int nextUserKey = 0;
   unsigned int i = 0;
   std::queue<Message*> userQueue;
   do
   {
      nextUserKey =  lastServed == users.size() - 1 ? 0 : lastServed++;
      if(users.end()) userQueue = users.find(nextUserKey)->second;
      i++;
   } while(userQueue.empty() && i<users.size());

   return (i-1) < users.size() ? nextUserKey : -1; //return -1, when all users queue is empty.*/


//void RoundRobin::addMsgToUserQueue(std::map<unsigned int, std::queue<Message*>>* users, Message* message)
//{
   // int key = message->getSrc();
   // users[key]->push(message);

   // if(users->find(key) == users->end()){
   //  users[key] = std::queue<Message*>;
   // }
   // std::queue<Message*>* userQueue = users.find(key);

   // userQueue->push(&message);
//}
