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
class CombinedData;

class Priority : public Prioritization
{
public:
  Priority(Queue<CombinedData*>& theFifo, PrioritizedQueue<CombinedData*>& thePrioQueue, const Ontology& ontology);
  virtual ~Priority();

private:
  void evaluate();

private:
  Queue<CombinedData*>& fifo;
  PrioritizedQueue<CombinedData*>& prioQueue;
  const Ontology& ontology;
};

#endif /* PRIORITY_H_ */
