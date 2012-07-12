/*
 * @brief MessageParser.cpp implementation of member functions
 */

#include "MessageParser.h"
#include "../Config.h"
#include "../Tools/ByteArray.h"
#include "../Tools/Exception.h"
#include "../DataManagement/DataTypes.h"

#include <iostream>


MessageParser::MessageParser()
{
}

MessageParser::~MessageParser()
{
}

void MessageParser::parse(const ByteArray& recv_data)
{
  std::cout << "\n---------------parser start---------------------------\n";
  version = recv_data.getByte(0).separate<0,4>();
  msgConfig = merge( recv_data.getByte(0).separate<4,8>(), recv_data.getByte(1) );

  std::cout << "version: " << version.to_uint() << "\n";
  std::cout << "config: 0x" << std::hex << msgConfig.to_uint() << std::dec << "\n";

  switch( static_cast<Version>(version.to_uint()) )
  {
    case VERSION_1: parse_v1(recv_data); break;
    default: std::cerr << "ERROR received unknown version\n"; break;
  }
}

void MessageParser::parse_v1(const ByteArray& data)
{
  std::cout << "\n---------------message---------------------------\n";
  curMsgPos = computeFirstDBByte();
  unsigned int msgLength = uchar2uint(&data.dataPtr()[curMsgPos - MSG_LENGTH_BYTES], MSG_LENGTH_BYTES);

  unsigned int crcSize = 0;
  if(msgLength < 0xFFFF)
    crcSize = MSG_CRC_16_BYTES;
  else
    crcSize = MSG_CRC_32_BYTES;

  std::cout << "msgLength: 0x" << std::hex << msgLength << std::dec << " = " << msgLength << "Bytes " << "\n";
  std::cout << "db_start: " << computeFirstDBByte() << "\n";
  std::cout << "crcSize: " << crcSize << "\n";

  cassert(msgLength < 0xFFFFFF);
  cassert(msgLength >= computeFirstDBByte());

  // parse datablocks
  while(curMsgPos + crcSize < msgLength)
  {
    parseDB(data);
  }

  std::cout << "---------------parser end---------------------------\n\n";
}

void MessageParser::parseDB(const ByteArray& data)
{
  std::cout << "\n---------------DBHeader---------------------------\n";
  // parse DB header
  Bin<10> dbDataType = merge( data.getByte(curMsgPos).separate<0, 8>(), data.getByte(curMsgPos+1).separate<0, 2>() );
  Bin<6> dbConfig = data.getByte(curMsgPos + 1).separate<2, 8>();
  unsigned int offset = DB_DATA_TYPE_CONFIG_BYTES;

  Bin<DB_DATA_OBJECT_ID_BYTES * BIT_PER_BYTE> dbDoid = uchar2Bin<DB_DATA_OBJECT_ID_BYTES * BIT_PER_BYTE>( &data.dataPtr()[curMsgPos + offset] );
  offset += DB_DATA_OBJECT_ID_BYTES;

  Bin<DB_SEQUENCE_NUMBER_BYTES * BIT_PER_BYTE> dbSequNum = uchar2Bin<DB_SEQUENCE_NUMBER_BYTES * BIT_PER_BYTE>( &data.dataPtr()[curMsgPos + offset] );
  offset += DB_SEQUENCE_NUMBER_BYTES;

  Bin<DB_LENGTH_BYTES * BIT_PER_BYTE> dbLengthBytes = uchar2Bin<DB_LENGTH_BYTES * BIT_PER_BYTE>( &data.dataPtr()[curMsgPos + offset] );
  offset += DB_LENGTH_BYTES;

//  std::cout << "curMsgPos: " << curMsgPos << " Bytes\n";
  std::cout << "dbDataType: 0x" << std::hex << dbDataType.to_uint() << std::dec << "\n";
  std::cout << "dbConfig: 0x" << std::hex << dbConfig.to_uint() << std::dec << "\n";
  std::cout << "dbDoid: 0x" << std::hex << dbDoid.to_uint() << std::dec << "\n";
  std::cout << "sequNum: 0x" << std::hex << dbSequNum.to_uint() << std::dec << "\n";
  std::cout << "dbLengthBytes: 0x" << std::hex << dbLengthBytes.to_uint() << " = " << std::dec << dbLengthBytes.to_uint() << " Bytes\n";

  cassert(dbLengthBytes < 0xFFFF);
  cassert(dbLengthBytes >= DB_HEADER_LENGTH_BYTES);

  // fill the received data block header with the parsed data
  DataBlock::Header dbh;
  dbh.config = dbConfig;
  dbh.dataObjectID = dbDoid;
  dbh.dataType = dbDataType;
  dbh.sequenceNumber = dbSequNum;
  dbh.length = dbLengthBytes;

  unsigned int contentPos = curMsgPos + offset;
//  std::cout << "contentPos: " << contentPos << " Bytes\n";

  switch( static_cast<DataTypes>(dbDataType.to_uint()) )
  {
    case TYPE_TEXT: textProcessing.start(dbh, &data[contentPos]); break;
    case TYPE_SENSOR: sensorProcessing.start(dbh, &data[contentPos]); break;
    case TYPE_PICTURE: pictureProcessing.start(dbh, &data[contentPos]); break;
  }

  curMsgPos += dbLengthBytes.to_uint();
}

const std::size_t MessageParser::computeFirstDBByte()
{
  // parse address type
  Bin<3> addrType = msgConfig.separate<0,3>();
  std::cout << "addrtype: " << addrType.to_uint() << "\n";

  unsigned int addrTypeLength = 0;
  switch( static_cast<AddressType>(addrType.to_uint()) )
  {
    case IP_V6: addrTypeLength = 2 * MSG_ADDRESS_TYPE_IPV6_BYTES; break;
    default: std::cerr << "ERROR: detected unknown address type\n"; throw;
  }

  return MSG_FIXED_HEADER_LENGTH_BYTES + addrTypeLength;
}
