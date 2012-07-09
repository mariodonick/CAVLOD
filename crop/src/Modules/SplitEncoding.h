/*
 * @brief SplitEncoding.h
 *
 */

#ifndef SPLITENCODING_H_
#define SPLITENCODING_H_

#include "Partitioning.h"

class Crodm;
template<class T> class Queue;
class DataBlock;

class SplitEncoding : public Partitioning
{
public:
  SplitEncoding(const Crodm& crodm, Queue<DataBlock*>& queue);
  virtual ~SplitEncoding();

private:
  void partText(const Bin<24>& doid, const std::string& content);
  void partSensor(const Bin<24>& doid, const float& value);

private:
  const Crodm& crodm;
  Queue<DataBlock*>& dbFifo;
};

#endif /* SPLITENCODING_H_ */
