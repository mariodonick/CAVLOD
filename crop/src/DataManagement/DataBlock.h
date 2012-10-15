/*
 * @brief DataBlock<DATA>.h
 *
 */

#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Bin.h"
#include "../TypesConfig/Pointer.h"
#include "../DataManagement/CrodtIO.h"
#include "../Tools/Timestamp.h"

#include <iosfwd>

class ByteArray;

class DataBlock
{
public:
  class Header
  {
  public:
    Header();
    virtual ~Header();
    void dump(std::ostream& out);

  public:
    DBDatatype dataType;
    DBConfig config;
    DBDataObjectID dataObjectID;
    DBSequenceNumber sequenceNumber;
    DBLength length;
  };

public:
  DataBlock();
  virtual ~DataBlock();

  void setHeader(const DataBlock::Header& dbh);

  const DBDataObjectID& getDataObjectID() const;
  const DBDatatype& getDataType() const;
  const DBSequenceNumber& getSequenceNumber() const;
  const DBConfig& getConfig() const;
  const DBLength& getLength() const;
  const float& getPriority() const;
  const RelevanceData& getRelevanceData() const;
  const CTimestamp& getTimestamp() const;

  void setDataObjectID(const DBDataObjectID& doid);
  void setDataType(const DBDatatype& dt);
  void setSequenceNumber(const DBSequenceNumber& sn);
  void setConfig(const DBConfig& conf);
  void setPriority(const float& prio);
  void setRelevanceData(const RelevanceData& rel);

  void stamp();
  void addContent(ByteArray_sPtr content);
  ByteArray_sPtr getContent();

  void dump(std::ostream& out);

private:
  float priority;
  RelevanceData relevance;
  Header header;

  ByteArray_sPtr content;
  Timestamp timestamp;
};


class CompareDB
{
  bool reverse;

public:
  CompareDB(const bool& revparam = false)
  {
    reverse = revparam;
  }
  bool operator() (const DataBlock_sPtr lhs, const DataBlock_sPtr rhs) const
  {
    if (reverse) return (lhs->getPriority() > rhs->getPriority());
    else return (lhs->getPriority() < rhs->getPriority());
  }
};


#endif /* DATABLOCK_H_ */
