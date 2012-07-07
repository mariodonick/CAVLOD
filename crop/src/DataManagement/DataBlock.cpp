/*
 * @brief DataBlock.cpp implementation of member functions
 */

#include "DataBlock.h"

#include "../Tools/Bin.h"
#include "../Tools/ByteArray.h"

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

void DataBlock::setHeader(const DataBlockHeader& dbh)
{
  header = dbh;
}

const Bin<24>& DataBlock::getDataObjectID() const
{
  return header.getDataObjectID();
}

const Bin<10>& DataBlock::getDataType() const
{
  return header.getDataType();
}

const HalfWord& DataBlock::getSequenceNumber() const
{
  return header.getSequenceNumber();
}

const Bin<6>& DataBlock::getConfig() const
{
  return header.getConfig();
}

const HalfWord& DataBlock::getLength() const
{
  return header.getLength();
}

const float& DataBlock::getPriority() const
{
  return priority;
}

void DataBlock::setDataObjectID(const Bin<24>& doid)
{
  header.setDataObjectID(doid);
}

void DataBlock::setDataType(const Bin<10>& dt)
{
  header.setDataType(dt);
}

void DataBlock::setSequenceNumber(const HalfWord& sn)
{
  header.setSequenceNumber(sn);
}

void DataBlock::setConfig(const Bin<6>& conf)
{
  header.setConfig(conf);
}

void DataBlock::setPriority(const float& prio)
{
  priority = prio;
}

void DataBlock::addContent(ByteArray* data)
{
  if(content == nullptr)
    content = data;
  else
    content->append( data->dataPtr(), data->size() );
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
