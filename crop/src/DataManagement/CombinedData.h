/*
 * @brief CombinedData.h
 *
 */

#ifndef COMBINEDDATA_H_
#define COMBINEDDATA_H_

#include "DataBlockHeader.h"

class ByteArray;

class CombinedData
{
public:
  CombinedData()
  : priority(0.f)
  {

  }
  virtual ~CombinedData(){}

public:
  float priority;
  DataBlockHeader header;

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
  bool operator() (const CombinedData* lhs, const CombinedData* rhs) const
  {
    if (reverse) return (lhs->priority > rhs->priority);
    else return (lhs->priority < rhs->priority);
  }
};

#endif /* COMBINEDDATA_H_ */
