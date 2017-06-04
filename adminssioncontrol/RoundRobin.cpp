#include "RoundRobin.h"

RoundRobin::RoundRobin() {
    acceptedCount = 0;
    rejectedCount = 0;
}

RoundRobin::~RoundRobin() {  }

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
               unsigned int key = message->getSrc();
               users[key].push_back(message);
               buffer.push_back(message); //bufor sluzy jedynie jako licznik do wyswietlania w EV!.
               if(std::find(usersOrdered2Served.begin(),usersOrdered2Served.end(),&users[key]) == usersOrdered2Served.end())
               {
                   usersOrdered2Served.push_back(&users[key]);
               }

               ++acceptedCount;
               scheduleAt(simTime() + messageHandlingTime, message);
           } else {
               ++rejectedCount;
           }
           EV << "Source IN: " << message->getSrc() << std::endl;
       } else {
           //showInfoAboutVariables();
          unsigned int key = (*usersOrdered2Served.front()).front()->getSrc();
          Message* sendMessage =users[key].front();
          if(sendMessage->isScheduled()) cancelEvent(sendMessage); //OBEJSCIE BLEDU!!!!!
          send(sendMessage, "out");


          buffer.erase(buffer.begin());
          users[key].erase(users[key].begin());
          usersOrdered2Served.erase(usersOrdered2Served.begin());
          if(!users[key].empty()){
            usersOrdered2Served.push_back(&users[key]);
          }
          //showInfoAboutVariables();
          EV << "SOURCE OUT: " << sendMessage->getSrc() << ", buffer size: " << buffer.size() << std::endl;
       }
   }

    EV  <<"BufferSize: " << buffer.size() << " Rejected: " << rejectedCount << " Accepted: " << acceptedCount << std::endl;

    emit(bufferSizeSignal, (long) buffer.size());
    emit(acceptedSignal, (long) acceptedCount);
    emit(rejectedSignal, (long) rejectedCount);
}






/*void RoundRobin::showVector(std::vector<Message*> vector)
{
    //std::cout<< "wartosc wektora to: ";
    for(auto it = vector.begin(); it!=vector.end(); ++it )
    {
        std::cout<< (*it)->getSrc() << ' ';
    }
    std::cout<< endl;
}

void RoundRobin::showVectorOfVectors(std::vector<std::vector<Message*>*> vector)
{
    for(unsigned int i=0; i< vector.size();i++)
    {
        showVector(*vector.at(i));
    }
}


void RoundRobin::showInfoAboutVariables()
{
    std::cout << "\t\t Adres mapy(users): " << &users <<endl;
    std::cout << "Klucze w mapie to: ";
    for(auto it = users.begin(); it != users.end(); ++it) {
        std::cout << it->first << ", ";
    }
    std::cout<< "\nAdresy wartoœci (wektorow userów) w mapie to: ";
    for(auto it = users.begin(); it != users.end(); ++it) {
        std::cout << &(it->second) << ", ";
    }
    std::cout <<"\nZawartosc wektorow w mapie to: \n";
    for(auto it = users.begin(); it != users.end(); ++it) {
        std::cout << "\tDla klucza: " << it->first << ": ";
        showVector(it->second);
    }

   std::cout << "\t\t Adres usersOrdered2Served: " << &usersOrdered2Served <<endl;
   std::cout<< "Adresy 'wewnetrznych' wektorow: ";
   for(auto it = usersOrdered2Served.begin(); it != usersOrdered2Served.end(); ++it) {
       std::cout << &it <<", ";
   }
   std::cout <<"\nAdresy wskaznikow 'wewnetrznych' wektorow: ";
   for(auto it = usersOrdered2Served.begin(); it != usersOrdered2Served.end(); ++it) {
       std::cout << &(*it) << ", ";
   }

   std::cout <<"\nAdresy ITeratora 'wewnetrznych' wektorow: ";


          for(unsigned int i=0; i< usersOrdered2Served.size();i++)
             {
                 std::cout << &(*usersOrdered2Served.at(i)) << ", ";
             }


   std::cout <<"\nZawartosc 'wewnetrznych' wektorow2: \n";
   showVectorOfVectors(usersOrdered2Served);

}*/




/*
 * Generalnie pomysl jest taki:
 *  1.Przys³an¹ wiadomoœæ dodaj do kolejki usera.
 *  2.Daj  kolejke usera, który jako kolejny zosta³ dodany do "mapy"
 *  3. Powtarzaj 2. Dopuki kolejka jest pusta
 *  4. Wez pierwsza wiadomosc z kolejki usera i daj ja do bufor.
 *  5. Usun pobrana wiadomosc z kolejki usera.
 *  6. lastServed = Klucz, do kolejki z ktorej zosta³a dodana do bufora pobrana wiadomosc.
 */

/*
 * Pomys³ 2:
 * 1. Msg zapisuj do mapy (odpowiedniej kolejki usera). <- users[message->getSrc()].push(message);
 * 2. Jesli jeszcze tej kolejki nie ma w usersOrdered2Served to j¹ dodaj (tylko referencje!). Ta zmeinna pomoze w ustalaniu obslugi msg.
 *
 * Przetwarzanie msg:
 * 3. Wez pierwsza kolejke z usersOrdered2Served do zmiennej.
 * 4. wez  pierwszy element Msg* z pobranej kolejki do zmiennej
 * 5. usun pobrana msg* z kolejki.
 * 6. Jesli kolejka nie jest pusta to dodaj ja na koniec   usersOrdered2Served.
 *  3-6 to metoda, i zwraca 4. czyli  msg* (planowana wiadomosc do oblslgi).
 *
 *  7.Przetworz wiadomosc;
 *
 * Tutaj zmienna bufor sluzy tylko za licznik!
 */
