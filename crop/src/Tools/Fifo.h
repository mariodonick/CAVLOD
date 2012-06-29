/*
 * @brief Fifo.h
 *
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "Queue.h"

#include <queue>

template<class T>
class Fifo : public Queue<T>
{
public:
  Fifo();
  virtual ~Fifo();

private:
  T pop();
  void push(const T& data);
  const bool isEmpty();
  void dump(std::ostream& out);
  const std::size_t size();

private:
  std::queue<T> queue;
};

template<class T>
Fifo<T>::Fifo()
{

}

template<class T>
Fifo<T>::~Fifo()
{

}

template<class T>
T Fifo<T>::pop()
{
  T value = queue.front();
  queue.pop();
  return value;
}

template<class T>
void Fifo<T>::push(const T& data)
{
  queue.push(data);
}

template<class T>
const bool Fifo<T>::isEmpty()
{
  return queue.empty();
}

template<class T>
const std::size_t Fifo<T>::size()
{
  return queue.size();
}

#endif /* FIFO_H_ */
