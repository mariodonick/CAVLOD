/*
 * @brief Priority.h
 *
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "Prioritization.h"

template<class T> class Queue;
class Ontology;
template<class T>
class PrioritizedQueue;
class DataBlock;

class Priority : public Prioritization
{
public:
  Priority(Queue<DataBlock*>& theFifo, PrioritizedQueue<DataBlock*>& thePrioQueue, const Ontology& ontology);
  virtual ~Priority();

private:
  void evaluate();

private:
  Queue<DataBlock*>& dbFifo;
  PrioritizedQueue<DataBlock*>& prioQueue;
  const Ontology& ontology;
};

#endif /* PRIORITY_H_ */
