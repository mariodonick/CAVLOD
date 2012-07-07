/*
 * @brief DataBlock<DATA>.h
 *
 */

#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include "DataBlockHeader.h"

#include <iosfwd>

class ByteArray;
template<unsigned int BAND_WIDTH>
class Bin;

class DataBlock
{
public:
  DataBlock();
  virtual ~DataBlock();

  ByteArray* getContent();

  void setHeader(const DataBlockHeader& dbh);

  const Bin<24>& getDataObjectID() const;
  const Bin<10>& getDataType() const;
  const HalfWord& getSequenceNumber() const;
  const Bin<6>& getConfig() const;
  const HalfWord& getLength() const;
  const float& getPriority() const;

  void setDataObjectID(const Bin<24>& doid);
  void setDataType(const Bin<10>& dt);
  void setSequenceNumber(const HalfWord& sn);
  void setConfig(const Bin<6>& conf);
  void setPriority(const float& prio);

  void addContent(ByteArray* content);

  void dump(std::ostream& out);

private:
  float priority;
  DataBlockHeader header;

  ByteArray* content;
};


class CompareDB
{
  bool reverse;
public:
  CompareDB(const bool& revparam = false)
  {
    reverse = revparam;
  }
  bool operator() (const DataBlock* lhs, const DataBlock* rhs) const
  {
    if (reverse) return (lhs->getPriority() > rhs->getPriority());
    else return (lhs->getPriority() < rhs->getPriority());
  }
};


#endif /* DATABLOCK_H_ */
