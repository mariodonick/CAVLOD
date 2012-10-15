/*
 * @brief MessageParser.cpp implementation of member functions
 */

#include "MessageParser.h"
#include "../Tools/ByteArray.h"
#include "../TypesConfig/Config.h"

#include <iostream>
#include <cassert>


MessageParser::MessageParser()
: config( *Config::instance() )
{
}

MessageParser::~MessageParser()
{
}

void MessageParser::parse(const ByteArray& recv_data)
{
  INFO() << "\n---------------parser start---------------------------\n";
  version = recv_data.getByte(0).separate<0,4>();
  msgConfig = merge( recv_data.getByte(0).separate<4,8>(), recv_data.getByte(1) );

  INFO() << "version: " << version.to_uint() << "\n";
  INFO() << "config: 0x" << std::hex << msgConfig.to_uint() << std::dec << "\n";

  switch( static_cast<EMsgVersion>(version.to_uint()) )
  {
    case VERSION_1: parse_v1(recv_data); break;
    default: ERROR() << "received unknown version\n"; break;
  }
}

void MessageParser::parse_v1(const ByteArray& data)
{
  INFO() << "\n---------------message---------------------------\n";
  curMsgPos = computeFirstDBByte();
  unsigned int msgLength = char2uint(&data.dataPtr()[curMsgPos - MSG_LENGTH_BYTES], MSG_LENGTH_BYTES);

  unsigned int crcSize = 0;
  if(msgLength < config.messageCrcBorder)
    crcSize = MSG_CRC_16_BYTES;
  else
    crcSize = MSG_CRC_32_BYTES;

  INFO() << "Message Length: 0x" << std::hex << msgLength << std::dec << " = " << msgLength << "Bytes " << "\n";
  DBG() << "db_start: " << computeFirstDBByte() << "\n";
  DBG() << "crcSize: " << crcSize << "\n";

  assert(msgLength < MAX_MSG_LENGTH);
  assert(msgLength >= computeFirstDBByte());

  // parse datablocks
  while(curMsgPos + crcSize < msgLength)
  {
    parseDB(data);
  }

  INFO() << "---------------parser end---------------------------\n\n";
}

void MessageParser::parseDB(const ByteArray& data)
{
  INFO() << "\n---------------DBHeader---------------------------\n";
  // parse DB header
  DBDatatype dbDataType = merge( data.getByte(curMsgPos).separate<0, 8>(), data.getByte(curMsgPos+1).separate<0, 2>() );
  DBConfig dbConfig = data.getByte(curMsgPos + 1).separate<2, 8>();
  unsigned int offset = DB_DATA_TYPE_CONFIG_BYTES;

  DBDataObjectID dbDoid = char2Bin<DB_DATA_OBJECT_ID_BYTES * BIT_PER_BYTE>( &data.dataPtr()[curMsgPos + offset] );
  offset += DB_DATA_OBJECT_ID_BYTES;

  DBSequenceNumber dbSequNum = char2Bin<DB_SEQUENCE_NUMBER_BYTES * BIT_PER_BYTE>( &data.dataPtr()[curMsgPos + offset] );
  offset += DB_SEQUENCE_NUMBER_BYTES;

  DBLength dbLengthBytes = char2Bin<DB_LENGTH_BYTES * BIT_PER_BYTE>( &data.dataPtr()[curMsgPos + offset] );
  offset += DB_LENGTH_BYTES;

  INFO() << "DB - DataType: 0x" << std::hex << dbDataType.to_uint() << std::dec << " = " << dataType2String(dbDataType) << "\n";
  INFO() << "DB - Config: 0x" << std::hex << dbConfig.to_uint() << std::dec << "\n";
  INFO() << "DB - Doid: 0x" << std::hex << dbDoid.to_uint() << std::dec << "\n";
  INFO() << "DB - Sequence Number: 0x" << std::hex << dbSequNum.to_uint() << std::dec << "\n";
  INFO() << "DB - Length: 0x" << std::hex << dbLengthBytes.to_uint() << " = " << std::dec << dbLengthBytes.to_uint() << " Bytes\n";

  assert(dbLengthBytes < config.messageCrcBorder);
  assert(dbLengthBytes >= DB_HEADER_LENGTH_BYTES);

  // fill the received data block header with the parsed data
  DataBlock::Header dbh;
  dbh.config = dbConfig;
  dbh.dataObjectID = dbDoid;
  dbh.dataType = dbDataType;
  dbh.sequenceNumber = dbSequNum;
  dbh.length = dbLengthBytes;

  unsigned int contentPos = curMsgPos + offset;

  switch( static_cast<DataTypes>(dbDataType.to_uint()) )
  {
    case TYPE_TEXT: textProcessing.start(dbh, &data[contentPos]); break;
    case TYPE_SENSOR: /*sensorProcessing.start(dbh, &data[contentPos]);*/ break; //todo wieder einkommentieren wenn fertig
  }

  curMsgPos += dbLengthBytes.to_uint();
}

const std::size_t MessageParser::computeFirstDBByte()
{
  // parse address type
  Bin<3> addrType = msgConfig.separate<0,3>();
  INFO() << "AddressType: " << addrType.to_uint() << "\n";

  unsigned int addrTypeLength = 0;
  switch( static_cast<MsgAddressType>(addrType.to_uint()) )
  {
    case IP_V6: addrTypeLength = 2 * MSG_ADDRESS_TYPE_IPV6_BYTES; break;
    default: ERROR() << "ERROR: detected unknown address type\n"; throw;
  }

  return MSG_FIXED_HEADER_LENGTH_BYTES + addrTypeLength;
}
