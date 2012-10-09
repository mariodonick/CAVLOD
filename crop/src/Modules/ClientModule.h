/*
 * @brief ClientModule.h
 *
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "UDPSocket.h"
#include "../Tools/PrioritizedQueue.h"
#include "../TypesConfig/Pointer.h"

#include <thread>
#include <list>
#include <mutex>

class ClientModule
{
public:
  ClientModule();
  virtual ~ClientModule();

  void run();
  void initialize();

private:
  void packetizerThread();

  void handleSensorEvent(const DBDataObjectID& id, const bool& usingTimestamp);
  void handleTextEvent(const DBDataObjectID& id, const bool& usingTimestamp);

private:
  bool running;

  DBQueue_uPtr dbFifo;
  DBQueue_uPtr prioQueue;

  TextInput_sPtr textInput;
  SensorInput_sPtr sensorInput;
  Crodm_uPtr crodm;
  NetworkIO_uPtr network;
  Partitioning_uPtr partitioning;
  Prioritization_uPtr prioritization;
  Packetizer_uPtr packetizer;

  std::list<std::thread> threads;

  std::mutex eventMutex;
};

#endif /* CLIENTMODULE_H_ */
