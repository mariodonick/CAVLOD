/*
 * @brief ClientModule.h
 *
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "UDPSocket.h"
#include "../Tools/PrioritizedQueue.h"

class DataBlock;
class Ontology;
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
  Queue<DataBlock*>* fifo;
  PrioritizedQueue<DataBlock*> prioQueue;

  Ontology* ontology;
  NetworkIO* network;
  Partitioning* partitioning;
  Prioritization* prioritization;
  Packetizer* packetizer;
};

#endif /* CLIENTMODULE_H_ */
