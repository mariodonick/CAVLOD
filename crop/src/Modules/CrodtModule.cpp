/*
 * @brief CrodtModule.cpp implementation of member functions
 */

#include "CrodtModule.h"
#include "SplitEncoding.h"
#include "Priority.h"
#include "CrodmFacade.h"
#include "UDPSocket.h"
#include "MessagePacketizer.h"

#include "../TypesConfig/Config.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Fifo.h"
#include "../Tools/SmartPrioritizedQueue.h"
#include "../Tools/ByteArray.h"
#include "../Tools/StopWatch.h"
#include "../Tools/Log.h"
#include "../Tools/PrioritizedQueue.h"
#include "../TypesConfig/Config.h"

CrodtModule::CrodtModule()
: running(false)
, config( *Config::instance() )
, dbFifo( new Fifo<DataBlock_sPtr> )
, prioQueue( new SmartPrioritizedQueue )
, crodm( new CrodmFacade )
, network( new UDPSocket )
, partitioning( new SplitEncoding(crodm, dbFifo) )
, prioritization( new Priority(dbFifo, prioQueue, crodm) )
, packetizer( new MessagePacketizer(prioQueue) )
, sensorId(0)
, textId(0)
{
  running = true;
  packerThread = std::thread( &CrodtModule::packetizerThread, this );

  INFO() << "client is up and running!\n";
}

CrodtModule::~CrodtModule()
{
  running = false;

  if( packerThread.joinable() )
    packerThread.join();

  Config::release();
}

void CrodtModule::initialize()
{
  //todo do some stuff eg: load dbs
}

void CrodtModule::packetizerThread()
{
  while( running )
  {
    usleep(config.sendDelayMS * 1000);

    INFO() << "start Sending... Data available in Prioritized Queue: " << prioQueue->size() << ENDL;

    const ByteArray& data = packetizer->packetizeMessage();

    if( !data.isEmpty() )
      network->sendData(data, config.ipAddress.c_str(), config.port);

    INFO() << "Sending... Data available in Prioritized Queue: " << prioQueue->size() << ENDL;
  }
}

void CrodtModule::sendText(const std::string& text, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  crodm->evaluateText(text, textId);
  partitioning->partText(textId, text, usingTimestamp);
  prioritization->evaluate();

  textId += 1;
  DBG() << "text STOP time: " << sw << ENDL;
}

void CrodtModule::sendSensor(const float& value, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  crodm->evaluateSensor(value, sensorId);
  partitioning->partSensor(sensorId, value, usingTimestamp);
  prioritization->evaluate();

  sensorId += 1;
  DBG() << "sensor STOP time: " << sw << ENDL;
}

