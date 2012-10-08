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
  std::list<DataBlock_sPtr> queue;

  std::mutex mutex;
};



SmartPrioritizedQueue::SmartPrioritizedQueue()
{

}

SmartPrioritizedQueue::~SmartPrioritizedQueue()
{

}

DataBlock_sPtr SmartPrioritizedQueue::pop(const std::size_t& size)
{
  // todo leere queue abfangen in dem leeres element zurück gegeben wird! oder nullptr oder sowas
  std::lock_guard<std::mutex> lock(mutex);

  std::list<DataBlock_sPtr>::iterator it = queue.begin();
  DataBlock_sPtr tmp;

  if(size != 0)
  {
    while( it != queue.end() )
    {
      if( (*it)->getLength() < size)
      {
        tmp = *it;
        queue.erase(it);
        break;
      }
      ++it;
    }
  }
  else
  {
    tmp = queue.front();
    queue.pop_front();
  }

  queue.sort( CompareDB() );

  return tmp;
}

void SmartPrioritizedQueue::push(const DataBlock_sPtr& data)
{
  std::lock_guard<std::mutex> lock(mutex);

  queue.push_back( data );
  queue.sort( CompareDB() );
}

const bool SmartPrioritizedQueue::isEmpty()
{
  return queue.empty();
}

const std::size_t SmartPrioritizedQueue::size()
{
  return queue.size();
}

#endif /* SMARTPRIORITIZEDQUEUE_H_ */
