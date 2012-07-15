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

class ClientModule
{
public:
  ClientModule();
  virtual ~ClientModule();

  void execute();

private:
  void packetizerThread();

private:
  DBQueue_uPtr dbFifo;
  DBQueue_uPtr prioQueue;

  Crodm_uPtr crodm;
  NetworkIO_uPtr network;
  Partitioning_uPtr partitioning;
  Prioritization_uPtr prioritization;
  Packetizer_uPtr packetizer;

  bool running;
  std::thread sendingThread;
};

#endif /* CLIENTMODULE_H_ */
