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
#include "../Tools/SmartPrioritizedQueue.h"
#include "../Tools/ByteArray.h"
#include "../Tools/StopWatch.h"
#include "../Tools/Log.h"
#include "../TypesConfig/Config.h"

#include <functional>

ClientModule::ClientModule()
: running(false)
, config( *Config::instance() )
, dbFifo( new Fifo<DataBlock_sPtr> )
, prioQueue( new SmartPrioritizedQueue )
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

  INFO() << "client is up and running!\n";
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
      ERROR() << "shuting down thread failed with: " << e.what() << ENDL;
    }
  }

  Config::release();
}

void ClientModule::initialize()
{
  //todo do some stuff eg: load dbs
}

void ClientModule::run()
{
  // hier die nebenläufigen gui etc starten, welche die events dann senden
  threads.push_back( std::thread( &ContentInput<std::string>::run, textInput) );
  threads.push_back( std::thread( &ContentInput<float>::run, sensorInput) );
}

void ClientModule::packetizerThread()
{
  while( running )
  {
    usleep(config.sendDelayMS * 1000); // todo auf events warten? variable schlafenszeiten? irgend etwas ausdenken

    INFO() << "start Sending... Data available in Prioritized Queue: " << prioQueue->size() << ENDL;

    const ByteArray& data = packetizer->packetizeMessage();

    if( !data.isEmpty() )
      network->sendData(data, config.ipAddress.c_str(), config.port);

    INFO() << "Sending... Data available in Prioritized Queue: " << prioQueue->size() << ENDL;
  }
}

//todo code dopplungen anders gestalten :(  -> templates? das schreit danach ;)
void ClientModule::handleTextEvent(const DBDataObjectID& id, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  const std::string& text = textInput->getInput();
  crodm->evaluateText(text, id);
  partitioning->partText(id, text, usingTimestamp);
  prioritization->evaluate();

  DBG() << "text STOP sw: " << sw << ENDL;
}

void ClientModule::handleSensorEvent(const DBDataObjectID& id, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  const float& value = sensorInput->getInput();
  crodm->evaluateSensor(value, id);
  partitioning->partSensor(id, value, usingTimestamp);
  prioritization->evaluate();

  DBG() << "sensor STOP sw: " << sw << ENDL;
}
