/*
 * @brief PrioritizedQueue.h
 *
 */

#ifndef PRIORITIZEDQUEUE_H_
#define PRIORITIZEDQUEUE_H_

#include "ByteArray.h"
#include "Queue.h"

#include <queue>
#include <mutex>
#include <algorithm>

#include "../DataManagement/DataBlock.h"

template<class T>
class PrioritizedQueue : public Queue<T>
{
public:
  PrioritizedQueue();
  virtual ~PrioritizedQueue();

  T pop();
  void push(const T& data);
  const bool isEmpty();
  const std::size_t size();

private:
  std::priority_queue<T, std::vector<T>, CompareDB > queue;

  std::mutex mutex;
};



template<class T>
PrioritizedQueue<T>::PrioritizedQueue()
: queue( CompareDB() )
{

}

template<class T>
PrioritizedQueue<T>::~PrioritizedQueue()
{

}

template<class T>
T PrioritizedQueue<T>::pop()
{
  std::lock_guard<std::mutex> lock(mutex);
  T tmp = queue.top();
//  std::cout << "pop priority: " << std::dec << tmp->first << "\n";
  queue.pop();

  return tmp;
}

template<class T>
void PrioritizedQueue<T>::push(const T& data)
{
  std::lock_guard<std::mutex> lock(mutex);
  queue.push( data );
}

template<class T>
const bool PrioritizedQueue<T>::isEmpty()
{
  return queue.empty();
}

template<class T>
const std::size_t PrioritizedQueue<T>::size()
{
  return queue.size();
}

#endif /* PRIORITIZEDQUEUE_H_ */
