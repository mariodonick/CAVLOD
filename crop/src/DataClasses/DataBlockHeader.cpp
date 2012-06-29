/*
 * @brief DataBlockHeader.cpp implementation of member functions
 */

#include "DataBlockHeader.h"
#include "DataTypes.h"
#include "../Config.h"

#include <iostream>

DataBlockHeader::DataBlockHeader()
: dataType(0)
, config(0)
, dataObjectID(0)
, sequenceNumber(0)
, length(DB_HEADER_LENGTH_BYTES)
{
}

DataBlockHeader::~DataBlockHeader()
{
}


const Bin<24>& DataBlockHeader::getDataObjectID() const
{
  return dataObjectID;
}

const Bin<10>& DataBlockHeader::getDataType() const
{
  return dataType;
}

const HalfWord& DataBlockHeader::getSequenceNumber() const
{
  return sequenceNumber;
}

const Bin<6>& DataBlockHeader::getConfig() const
{
  return config;
}

const HalfWord& DataBlockHeader::getLength() const
{
  return length;
}

void DataBlockHeader::setDataObjectID(const Bin<24>& doid)
{
  dataObjectID = doid;
}

void DataBlockHeader::setDataType(const Bin<10>& dt)
{
  dataType = dt;
}

void DataBlockHeader::setSequenceNumber(const HalfWord& sn)
{
  sequenceNumber = sn;
}

void DataBlockHeader::setConfig(const Bin<6>& conf)
{
  config = conf;
}

void DataBlockHeader::setLength(const unsigned int& len)
{
  length = len;
}

void DataBlockHeader::setLength(const Bin<16>& len)
{
  length = len;
}

void DataBlockHeader::dump(std::ostream& out)
{
  out << "DataType: " << dataType2String(dataType.to_ulong()) << "\n"
      << "Config: " << std::hex << config.to_ulong() << std::dec << "\n"
      << "DataObjectID: " << dataObjectID.to_ulong() << "\n"
      << "SequenceNumber: " << sequenceNumber.to_ulong() << "\n"
      << "Length: " << length.to_ulong() << "\n";
}
