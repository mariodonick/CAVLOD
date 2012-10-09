/*
 * @brief smartPrioritizedQueue.h
 *
 */

#ifndef SMARTPRIORITIZEDQUEUE_H_
#define SMARTPRIORITIZEDQUEUE_H_

#include "Queue.h"

#include <list>
#include <mutex>

#include "../DataManagement/DataBlock.h"

class SmartPrioritizedQueue : public Queue<DataBlock_sPtr>
{
public:
  SmartPrioritizedQueue();
  virtual ~SmartPrioritizedQueue();

  DataBlock_sPtr pop(const std::size_t& size = 0);
  void push(const DataBlock_sPtr& data);
  const bool isEmpty();
  const std::size_t size();

private:
  void sort();

private:
  std::list<DataBlock_sPtr> queue;

  std::mutex mutex;
};

#endif /* SMARTPRIORITIZEDQUEUE_H_ */
