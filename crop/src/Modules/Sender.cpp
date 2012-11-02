/*
 * @brief SenderModule.cpp implementation of member functions
 */

#include "Sender.h"
#include "SplitEncoding.h"
#include "Priority.h"
#include "CrodmFacade.h"
#include "UDPSocket.h"
#include "MessagePacketizer.h"
#include "LocalStoreManager.h"
#include "SmartPrioritizedQueue.h"

#include "../TypesConfig/Config.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Fifo.h"
#include "../Tools/ByteArray.h"
#include "../Tools/StopWatch.h"
#include "../Tools/Log.h"
#include "../TypesConfig/Config.h"
#include "../DataManagement/CrodtIO.h"

using namespace crodt;

Sender::Sender()
: running(false)
, config( *Config::instance() )
, dbFifo( new Fifo<DataBlock_sPtr> )
, prioQueue( new SmartPrioritizedQueue )
, dbStorage(new LocalStoreManager)
, crodm( new CrodmFacade )
, network( new UDPSocket )
, partitioning( new SplitEncoding(crodm, dbFifo) )
, prioritization( new Priority(dbFifo, prioQueue, crodm, dbStorage) )
, packetizer( new MessagePacketizer(prioQueue, dbStorage) )
, sensorId(0)
, textId(0)
{
  running = true;
  packerThread = std::thread( &Sender::packetizerThread, this );

  INFO() << "client is up and running!" << ENDL;
}

Sender::~Sender()
{
  running = false;

  if( packerThread.joinable() )
    packerThread.join();

  Config::release();
}

void Sender::initialize()
{
  const std::vector<DataBlock_sPtr>& dbVec = dbStorage->load();

  for(std::vector<DataBlock_sPtr>::const_iterator it = dbVec.begin(); it != dbVec.end(); ++it)
    prioQueue->push(*it);
}

void Sender::packetizerThread()
{
  while( running )
  {
    usleep(config.sendDelayMS * 1000);

    INFO() << "Data available in Prioritized Queue: " << prioQueue->size() << ENDL;

    const ByteArray& data = packetizer->packetizeMessage();

    if( !data.isEmpty() )
    {
      network->sendData(data, config.ipAddress.c_str(), config.sendPort);
      INFO() << "Sending....... Data available in Prioritized Queue: " << prioQueue->size() << ENDL;
    }
  }
}

void Sender::sendText(const std::string& text, const bool& usingTimestamp)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  crodm->evaluateText(text, textId);
  partitioning->partText(textId, text, usingTimestamp);
  prioritization->evaluate();

  textId += 1;
  std::stringstream ss;
  ss << sw << " ";
  sw.dumpUS(ss);
  sw.dumpMS(ss);
  ss << "\n";
  std::cout << ss.str();
}

void Sender::sendText(const CrodtInput& ci)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  crodm->evaluateText(ci, textId);
  partitioning->partText(textId, ci.content, ci.is_timestamp);
  prioritization->evaluate();

  textId += 1;
  std::stringstream ss;
  ss << sw << " ";
  sw.dumpUS(ss); ss << " ";
  sw.dumpMS(ss); ss << "\n";
  std::cout << ss.str();
}

void Sender::sendSensor(const float& value)
{
  std::unique_lock<std::mutex> lock(eventMutex);

  StopWatch sw;
  crodm->evaluateSensor(value, sensorId);
  partitioning->partSensor(sensorId, value);
  prioritization->evaluate();

  sensorId += 1;
  DBG() << "sensor STOP time: " << sw << ENDL;
}

