/*
 * @brief Priority.h
 *
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "Prioritization.h"

template<class T> class Queue;
class Crodm;
template<class T>
class PrioritizedQueue;
class DataBlock;

class Priority : public Prioritization
{
public:
  Priority(Queue<DataBlock*>& theFifo, PrioritizedQueue<DataBlock*>& thePrioQueue, const Crodm& crodm);
  virtual ~Priority();

private:
  void evaluate();

private:
  Queue<DataBlock*>& dbFifo;
  PrioritizedQueue<DataBlock*>& prioQueue;
  const Crodm& crodm;
};

#endif /* PRIORITY_H_ */
