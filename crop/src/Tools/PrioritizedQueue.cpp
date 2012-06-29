/*
 * @brief PrioritizedQueue.cpp implementation of member functions
 */

#include "PrioritizedQueue.h"
#include "ByteArray.h"

PrioritizedQueue::PrioritizedQueue()
{

}

PrioritizedQueue::~PrioritizedQueue()
{

}

ByteArray* PrioritizedQueue::pop()
{
  std::map<float, ByteArray*>::iterator tmp = queue.begin();
//  std::cout << "pop priority: " << std::dec << tmp->first << "\n";
  ByteArray* value = tmp->second;
  queue.erase(tmp);

  return value;
}

void PrioritizedQueue::push(const float& key, ByteArray* data)
{
  queue.insert( std::make_pair(key, data) );
}

const bool PrioritizedQueue::isEmpty()
{
  return queue.empty();
}

const std::size_t PrioritizedQueue::size()
{
  return queue.size();
}
