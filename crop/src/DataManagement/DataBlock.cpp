/*
 * @brief DataBlock.cpp implementation of member functions
 */

#include "DataBlock.h"

#include "../Tools/Bin.h"
#include "../Tools/ByteArray.h"
#include "DataTypes.h"

DataBlock::DataBlock()
: priority(0.f)
, content(nullptr)
{
}

DataBlock::~DataBlock()
{
  if(content != nullptr)
    delete content;
}

void DataBlock::setHeader(const DataBlock::Header& dbh)
{
  header = dbh;
}

const Bin<24>& DataBlock::getDataObjectID() const
{
  return header.dataObjectID;
}

const Bin<10>& DataBlock::getDataType() const
{
  return header.dataType;
}

const HalfWord& DataBlock::getSequenceNumber() const
{
  return header.sequenceNumber;
}

const Bin<6>& DataBlock::getConfig() const
{
  return header.config;
}

const HalfWord& DataBlock::getLength() const
{
  return header.length;
}

const float& DataBlock::getPriority() const
{
  return priority;
}

void DataBlock::setDataObjectID(const Bin<24>& doid)
{
  header.dataObjectID = doid;
}

void DataBlock::setDataType(const Bin<10>& dt)
{
  header.dataType = dt;
}

void DataBlock::setSequenceNumber(const HalfWord& sn)
{
  header.sequenceNumber = sn;
}

void DataBlock::setConfig(const Bin<6>& conf)
{
  header.config = conf;
}

void DataBlock::setPriority(const float& prio)
{
  priority = prio;
}

void DataBlock::setLength(const HalfWord& length)
{
  header.length = length;
}

void DataBlock::addContent(ByteArray* data)
{
  if(content == nullptr)
    content = data;
  else
    content->append( data->dataPtr(), data->size() );

  header.length += data->size();
}

ByteArray* DataBlock::getContent()
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
, length(DB_HEADER_LENGTH_BYTES)
{

}

DataBlock::Header::~Header()
{

}

void DataBlock::Header::dump(std::ostream& out)
{
  out << "DataType: " << dataType2String(dataType.to_ulong()) << "\n"
      << "Config: " << std::hex << config.to_ulong() << std::dec << "\n"
      << "DataObjectID: " << dataObjectID.to_ulong() << "\n"
      << "SequenceNumber: " << sequenceNumber.to_ulong() << "\n";
}
