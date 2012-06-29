/*
 * @brief PrioritizedQueue.h
 *
 */

#ifndef PRIORITIZEDQUEUE_H_
#define PRIORITIZEDQUEUE_H_

#include "ByteArray.h"

#include <map>

//todo interface bauen
class ByteArray;

struct PriorityCompare
{
  bool operator() (const float& lhs, const float& rhs) const
  {return lhs > rhs;}
};


class PrioritizedQueue
{
public:
  PrioritizedQueue();
  virtual ~PrioritizedQueue();

  ByteArray* pop();
  void push(const float& key, ByteArray* data);
  const bool isEmpty();
  const std::size_t size();

private:
  std::map<float, ByteArray*, PriorityCompare> queue;
};

#endif /* PRIORITIZEDQUEUE_H_ */
