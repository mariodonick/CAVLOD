/*
 * @brief Queue.h
 *
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iosfwd>

template<class T>
class Queue
{
public:
  virtual ~Queue(){}

  virtual T pop() = 0;
  virtual void push(const T& data) = 0;
  virtual const bool isEmpty() = 0;
  virtual const std::size_t size() = 0;
};

#endif /* QUEUE_H_ */
