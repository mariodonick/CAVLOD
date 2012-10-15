/*
 * @brief smartPrioritizedQueue.h
 *
 */

#ifndef SMARTPRIORITIZEDQUEUE_H_
#define SMARTPRIORITIZEDQUEUE_H_

#include <list>
#include <mutex>

#include "../Tools/Queue.h"
#include "../DataManagement/DataBlock.h"

namespace crodt
{

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

} // namespace crodt

#endif /* SMARTPRIORITIZEDQUEUE_H_ */
