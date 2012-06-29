/*
 * @brief Priority.h
 *
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "Prioritization.h"

class ByteArray;
template<class T> class Queue;
class Ontology;
class PrioritizedQueue;

class Priority : public Prioritization
{
public:
  Priority(Queue<ByteArray*>& theFifo, PrioritizedQueue& thePrioQueue, const Ontology& ontology);
  virtual ~Priority();

private:
  void evaluate();

private:
  Queue<ByteArray*>& fifo;
  PrioritizedQueue& prioQueue;
  const Ontology& ontology;
};

#endif /* PRIORITY_H_ */
