/*
 * @brief SmartPrioritizedQueue.cpp implementation of member functions
 */

#include "SmartPrioritizedQueue.h"


SmartPrioritizedQueue::SmartPrioritizedQueue()
{

}

SmartPrioritizedQueue::~SmartPrioritizedQueue()
{

}

// return the next element which is smaller or equal to the given size otherwise this function return a nullptr
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

  sort();

  return tmp;
}

void SmartPrioritizedQueue::push(const DataBlock_sPtr& data)
{
  std::lock_guard<std::mutex> lock(mutex);
  queue.push_back( data );
  sort();
}

const bool SmartPrioritizedQueue::isEmpty()
{
  return queue.empty();
}

const std::size_t SmartPrioritizedQueue::size()
{
  return queue.size();
}

// have to sort backwards otherwise we send lower priority first
void SmartPrioritizedQueue::sort()
{
  queue.sort( CompareDB(true) );
}
