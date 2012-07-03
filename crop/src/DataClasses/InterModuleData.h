/*
 * @brief InterModuleData.h
 *
 */

#ifndef INTERMODULEDATA_H_
#define INTERMODULEDATA_H_

class ByteArray;

class PrioQueueData
{
public:
  PrioQueueData()
  : priority(0.f)
  {

  }
  virtual ~PrioQueueData(){}

public:
  float priority;
  ByteArray* content;
};

class Comparison
{
  bool reverse;
public:
  Comparison(const bool& revparam=false)
  {
    reverse=revparam;
  }
  bool operator() (const PrioQueueData* lhs, const PrioQueueData* rhs) const
  {
    if (reverse) return (lhs->priority > rhs->priority);
    else return (lhs->priority < rhs->priority);
  }
};

#endif /* INTERMODULEDATA_H_ */
