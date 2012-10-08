/*
 * packatizer.cpp
 *
 *  Created on: 04.06.2012
 *      Author: gigi
 */

#include "MessagePacketizer.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../TypesConfig/ProtocolConstants.h"
#include "../Tools/PrioritizedQueue.h"
#include "../DataManagement/DataBlock.h"


// todo die gehören woanders hin
// message
const MsgSrcAddress SRC_ADDRESS = 127001;
const MsgDstAddress DST_ADDRESS = 19216823;
const MsgConfig MESSAGE_CONFIG = 0;

MessagePacketizer::MessagePacketizer(DBQueue_uPtr& thePrioQueue)
: prioQueue(thePrioQueue)
{

}

MessagePacketizer::~MessagePacketizer()
{
}

// if the prioritized queue is empty this function return a empty bytearray
// otherwise this return the current message
const ByteArray& MessagePacketizer::packetizeMessage()
{
  // if queue is empty we return an empty datablock
  if( prioQueue->isEmpty() )
  {
    message.clear();
    return message;
  }

  //get first datablock
  DataBlock_sPtr first_db = prioQueue->pop();
  // compute first db length
  unsigned int msgLength = first_db->getLength().to_uint();
//  std::cout << "first db length: " << msgLength << std::endl;

  // check first db length
  const std::size_t max_msg_length = (first_db->getLength().to_uint() > MSG_CRC_LENGTH_BORDER) ? MAX_MSG_LENGTH : MSG_CRC_LENGTH_BORDER;

  ByteArray tmpContent;
  tmpContent.insert( first_db->getDataType() );
  tmpContent.append( first_db->getConfig() );
  tmpContent.append( first_db->getDataObjectID() );
  tmpContent.append( first_db->getSequenceNumber() );

  unsigned int offset = (first_db->getConfig()[DB_CONFIG_TIMESTAMP] == true) ? C_TIMESTAMP_BYTES : 0;
  tmpContent.append( first_db->getLength() + offset );

  if(first_db->getConfig()[DB_CONFIG_TIMESTAMP] == true)
  {
//    std::cout << "insert timestamp!" << std::endl;
    tmpContent.append( first_db->getTimestamp() );
    msgLength += C_TIMESTAMP_BYTES;
  }

  tmpContent.append(first_db->getContent()->dataPtr(), first_db->getContent()->size());

  // pack more db to the message
  // cancel if there is no other datablocks or the message is to long
  while( msgLength < 0xFF && !prioQueue->isEmpty() ) // todo here should stand max_msg_length -> complicate computation (specially msg and db lengths)
  {
    // get next datablocks
    DataBlock_sPtr next_db = prioQueue->pop();
    unsigned int tmp_length = next_db->getLength().to_uint();

    // insert header and content data
    tmpContent.append( next_db->getDataType() );
    tmpContent.append( next_db->getConfig() );
    tmpContent.append( next_db->getDataObjectID() );
    tmpContent.append( next_db->getSequenceNumber() );

    unsigned int offset = (first_db->getConfig()[DB_CONFIG_TIMESTAMP] == true) ? C_TIMESTAMP_BYTES : 0;
    tmpContent.append( next_db->getLength() + offset );

    if(first_db->getConfig()[DB_CONFIG_TIMESTAMP] == true)
    {
      tmpContent.append( first_db->getTimestamp() );
//      std::cout << "insert timestamp!" << std::endl;
      msgLength += C_TIMESTAMP_BYTES;
    }
    tmpContent.append( next_db->getContent()->dataPtr(), next_db->getContent()->size());

    msgLength += tmp_length;
//    std::cout << "msgLength " << msgLength << "\n";
  }

  // compute message length
  MsgLength messageLength = msgLength + MSG_FIXED_HEADER_LENGTH_BYTES + 2*MSG_ADDRESS_TYPE_IPV6_BYTES;
  messageLength += (messageLength >= MSG_CRC_LENGTH_BORDER) ? 4 : 2;

//  std::cout << "messageLength: " << messageLength.to_uint() << std::endl;

  // append message header
  message.insert(static_cast<MsgVersion>(VERSION_1) );
  message.append(MESSAGE_CONFIG); // todo message config genauer angeben/ iwo auslesen
  message.append(SRC_ADDRESS);
  message.append(DST_ADDRESS);
  message.append(messageLength);

  // append all datablocks
  message.append( tmpContent.dataPtr(), tmpContent.size() );

  //append crc
  if(messageLength >= MSG_CRC_LENGTH_BORDER)
  {
    const MsgCrc32 CRC_32 = computeCrc32();
    message.append(CRC_32);
  }
  else
  {
    const MsgCrc16 CRC_16 = computeCrc16();
    message.append(CRC_16);
  }

  return message;
}

const MsgCrc32 MessagePacketizer::computeCrc32()
{
  //todo crc computing here!
  return 32;
}

const MsgCrc16 MessagePacketizer::computeCrc16()
{
  //todo crc computing here!
  return 16;
}

