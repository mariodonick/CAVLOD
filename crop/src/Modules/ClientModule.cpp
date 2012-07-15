/*
 * @brief ClientModule.cpp implementation of member functions
 */

#include "ClientModule.h"
#include "SplitEncoding.h"
#include "Priority.h"
#include "CrodmFacade.h"
#include "UDPSocket.h"
#include "MessagePacketizer.h"

#include "../TypesConfig/Config.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Fifo.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/ByteArray.h"

ClientModule::ClientModule()
: dbFifo(new Fifo<DataBlock_sPtr>)
, prioQueue(new PrioritizedQueue<DataBlock_sPtr>)
, crodm(new CrodmFacade)
, network(new UDPSocket)
, partitioning( new SplitEncoding(crodm, dbFifo) )
, prioritization(new Priority(dbFifo, prioQueue, crodm))
, packetizer(new MessagePacketizer(prioQueue))
, running(false)
{
  running = true;
  sendingThread = std::thread( &ClientModule::packetizerThread, this );
  std::clog << "client is up and running!\n";
}

ClientModule::~ClientModule()
{
  running = false;

  usleep(200);

  sendingThread.join();
}

void ClientModule::execute()
{
  DBDataObjectID doid = 0;

  unsigned int loops = 1;
  std::cout << "How many data you want to send? Number of data:\n";
  std::cin >> loops;

  while(doid < loops)
  {
    std::string text = "Es folgt ein Beispieltext:\n";
    text.append("Hallo ich bin ein Beispieltext und komme vom Mars.\n");
    text.append("Dabei wurde ich zuerst zerstückelt, dann priorisiert, einzeln versendet und auf der Erde wieder zusammengesetzt.\n");

    // with the following lines you can insert spaces
//  std::cout << "Bitte einen Text eingeben:\n";
//  std::string text;

//  std::cin.clear(); //clean cin and wait for input
//  std::cin.sync();
//  std::cin.get();
//  std::getline(std::cin, text);
//  std::cout << "Eingabe text: " << text << "\n";

    doid += 1;
    crodm->evaluateText(text);
    partitioning->partText(doid, text);
    prioritization->evaluate();
  }

  std::clog << "content reading and processing is done\n";
}

void ClientModule::packetizerThread()
{
  while( running )
  {
    usleep(SLEEP_SECONDS*1000*1000); // todo auf events warten? variable schlafenszeiten? irgend etwas ausdenken

    const ByteArray& data = packetizer->packetizeMessage();
    if( !data.isEmpty() )
      network->sendData(data, IP_ADDRESS, PORT);

    std::cout << "Sending... Data available in Prioritized Queue: " << prioQueue->size() << "\n";
  }
}
