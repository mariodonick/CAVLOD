/*
 * @brief ClientModule.cpp implementation of member functions
 */

#include "ClientModule.h"
#include "SplitEncoding.h"
#include "Priority.h"
#include "CrodmFacade.h"
#include "UDPSocket.h"
#include "MessagePacketizer.h"
#include "TextInput.h"
#include "SensorInput.h"

#include "../TypesConfig/Config.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Fifo.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/ByteArray.h"
#include "../Tools/StopWatch.h"

#include <functional>

ClientModule::ClientModule()
: running(false)
, dbFifo( new Fifo<DataBlock_sPtr> )
, prioQueue( new PrioritizedQueue<DataBlock_sPtr> )
, textInput( new TextInput( running, std::bind(&ClientModule::handleTextEvent, this, std::placeholders::_1, std::placeholders::_2) ) )
, sensorInput( new SensorInput( running, std::bind(&ClientModule::handleSensorEvent, this, std::placeholders::_1, std::placeholders::_2) ) )
, crodm( new CrodmFacade )
, network( new UDPSocket )
, partitioning( new SplitEncoding(crodm, dbFifo) )
, prioritization( new Priority(dbFifo, prioQueue, crodm) )
, packetizer( new MessagePacketizer(prioQueue) )
{
  running = true;
  threads.push_back( std::thread( &ClientModule::packetizerThread, this ) );

  std::clog << "client is up and running!\n";
}

ClientModule::~ClientModule()
{
  running = false;

  for(std::list<std::thread>::iterator it = threads.begin(); it != threads.end(); ++it)
  {
    try
    {
      if( it->joinable() )
        it->join();
    }
    catch(std::system_error& e)
    {
      std::cerr << "shuting down thread failed with: " << e.what() << std::endl;
    }
  }
}

void ClientModule::start()
{
  // hier die nebenläufigen gui etc starten, welche die events dann senden
  threads.push_back( std::thread( &ContentInput<std::string>::run, textInput) );
  threads.push_back( std::thread( &ContentInput<float>::run, sensorInput) );
//  textInput->initial(); // todo notwendig?
//  sensorInput->initial();
}

void ClientModule::packetizerThread()
{
  while( running )
  {
    usleep(SLEEP_MSECONDS_PACKETIZER * 1000); // todo auf events warten? variable schlafenszeiten? irgend etwas ausdenken

    std::cout << "start Sending... Data available in Prioritized Queue: " << prioQueue->size() << std::endl;

    const ByteArray& data = packetizer->packetizeMessage();
//    data.dumpHex(std::cout);

    if( !data.isEmpty() )
      network->sendData(data, IP_ADDRESS, PORT);

    std::cout << "Sending... Data available in Prioritized Queue: " << prioQueue->size() << std::endl;
  }
}

//todo code dopplungen anders gestalten :(  -> templates? das schreit danach ;)
void ClientModule::handleTextEvent(const DBDataObjectID& id, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  const std::string& text = textInput->getInput();
  crodm->evaluateText(text);
  partitioning->partText(id, text, usingTimestamp);
  prioritization->evaluate();

  std::cout << "text STOP sw: " << sw << std::endl;
}

void ClientModule::handleSensorEvent(const DBDataObjectID& id, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  const float& value = sensorInput->getInput();
  crodm->evaluateSensor(value);
  partitioning->partSensor(id, value, usingTimestamp);
  prioritization->evaluate();

  std::cout << "sensor STOP sw: " << sw << std::endl;
}
