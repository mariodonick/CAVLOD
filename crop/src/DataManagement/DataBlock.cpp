/*
 * @brief DataBlock.cpp implementation of member functions
 */

#include "DataBlock.h"

#include "../Tools/ByteArray.h"
#include "../TypesConfig/Constants.h"
#include "DataTypes.h"

using namespace crodt;

DataBlock::DataBlock()
: priority(0.f)
, content(nullptr)
{
}

DataBlock::~DataBlock()
{
}

void DataBlock::setHeader(const DataBlock::Header& dbh)
{
  header = dbh;
}

const DataBlock::Header& DataBlock::getHeader() const
{
  return header;
}

const DBDataObjectID& DataBlock::getDataObjectID() const
{
  return header.dataObjectID;
}

const DBDatatype& DataBlock::getDataType() const
{
  return header.dataType;
}

const DBSequenceNumber& DataBlock::getSequenceNumber() const
{
  return header.sequenceNumber;
}

const DBConfig& DataBlock::getConfig() const
{
  return header.config;
}

const DBLength& DataBlock::getLength() const
{
  return header.length;
}

const float& DataBlock::getPriority() const
{
  return priority;
}

const RelevanceData& DataBlock::getRelevanceData() const
{
  return relevance;
}

const CTimestamp& DataBlock::getTimestamp() const
{
  return timestamp.getTime();
}

void DataBlock::setDataObjectID(const DBDataObjectID& doid)
{
  header.dataObjectID = doid;
}

void DataBlock::setDataType(const DBDatatype& dt)
{
  header.dataType = dt;
}

void DataBlock::setSequenceNumber(const DBSequenceNumber& sn)
{
  header.sequenceNumber = sn;
}

void DataBlock::setConfig(const DBConfig& conf)
{
  header.config = conf;
}

void DataBlock::setPriority(const float& prio)
{
  priority = prio;
}

void DataBlock::setRelevanceData(const RelevanceData& rel)
{
  relevance = rel;
}

void DataBlock::setTimestamp(const CTimestamp& ts)
{
  timestamp.setTimestamp(ts);
}

void DataBlock::stamp()
{
  timestamp.stamp();
}

void DataBlock::insertContent(ByteArray_sPtr data)
{
  content = data;
  header.length = data->size() + DB_HEADER_LENGTH_BYTES;
}

ByteArray_sPtr DataBlock::getContent()
{
  return content;
}

void DataBlock::dump(std::ostream& out)
{
  header.dump(out);
  out << "Content: \n";
  content->dumpHex(out);
}



DataBlock::Header::Header()
: dataType(0)
, config(0)
, dataObjectID(0)
, sequenceNumber(0)
, length(0)
{

}

DataBlock::Header::~Header()
{

}

void DataBlock::Header::dump(std::ostream& out)
{
  out << "DataType: " << dataType2String( static_cast<DataTypes>(dataType.to_ulong()) ) << "\n"
      << "Config: " << std::hex << config.to_ulong() << std::dec << "\n"
      << "DataObjectID: " << dataObjectID.to_ulong() << "\n"
      << "SequenceNumber: " << sequenceNumber.to_ulong() << "\n";
}
