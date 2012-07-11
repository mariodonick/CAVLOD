/*
 * @brief ClientModule.h
 *
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "UDPSocket.h"
#include "../Tools/PrioritizedQueue.h"

#include <thread>

class DataBlock;
class Crodm;
class Partitioning;
class Prioritization;
template<class T> class Queue;
class NetworkIO;
class Packetizer;

class ClientModule
{
public:
  ClientModule();
  virtual ~ClientModule();

  void execute();

private:
  void packetizerThread();

private:
  Queue<DataBlock*>* dbFifo;
  Queue<DataBlock*>* prioQueue;

  Crodm* crodm;
  NetworkIO* network;
  Partitioning* partitioning;
  Prioritization* prioritization;
  Packetizer* packetizer;

  bool running;
  std::thread sendingThread;
};

#endif /* CLIENTMODULE_H_ */
