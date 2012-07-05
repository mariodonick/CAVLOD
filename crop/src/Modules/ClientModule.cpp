/*
 * @brief ClientModule.cpp implementation of member functions
 */

#include "ClientModule.h"
#include "SplitEncoding.h"
#include "Priority.h"
#include "OntologyFacade.h"
#include "UDPSocket.h"
#include "MessagePacketizer.h"

#include "../Tools/Fifo.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/ByteArray.h"


ClientModule::ClientModule()
: fifo(new Fifo<CombinedData*>)
, ontology(new OntologyFacade)
, network(new UDPSocket)
, partitioning( new SplitEncoding(*ontology, *fifo) )
, prioritization(new Priority(*fifo, prioQueue, *ontology))
, packetizer(new MessagePacketizer(prioQueue))
{

}

ClientModule::~ClientModule()
{
  delete packetizer;
  delete prioritization;
  delete partitioning;
  delete network;
  delete ontology;
  delete fifo;
}

void ClientModule::execute()
{
  std::string text = "Es folgt ein Beispieltext:\n";
  text.append("Hallo ich bin ein Beispieltext und komme vom Mars.\n");
  text.append("Dabei wurde ich zuerst zerstückelt, dann priorisiert, einzeln versendet und auf der Erde wieder zusammengesetzt.");

//  std::cout << "Bitte einen Text eingeben:\n";
//  std::string text;
//  // so you can insert spaces
//  std::cin.clear(); //clean cin and wait for input
//  std::cin.sync();
//  std::cin.get();
//  std::getline(std::cin, text);
//  std::cout << "Eingabe text: " << text << "\n";

  partitioning->partText(1, text);
  prioritization->evaluate();

  while( !prioQueue.isEmpty() )
  {
    sleep(SLEEP_SECONDS);

    ByteArray arr = packetizer->packetizeMessage();
    network->sendData(arr, IP_ADDRESS, PORT);
  }
}
