/*
 * packatizer.cpp
 *
 *  Created on: 04.06.2012
 *      Author: Florian Ludwig
 */

#include "MessagePacketizer.h"
#include "SmartPrioritizedQueue.h"
#include "LocalStoreManager.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../TypesConfig/Constants.h"
#include "../TypesConfig/Config.h"
#include "../Tools/IPTools.h"
#include "../DataManagement/DataBlock.h"

using namespace crodt;

MessagePacketizer::MessagePacketizer(DBQueue_uPtr& thePrioQueue, StoreManager_uPtr& storage)
: prioQueue(thePrioQueue)
, dbStorage(storage)
{

}

MessagePacketizer::~MessagePacketizer()
{
}
unsigned int ii = 0;
// if the prioritized queue is empty this function return an empty bytearray
// otherwise this return the current message
const ByteArray& MessagePacketizer::packetizeMessage()
{
  Config* config = Config::instance();

  // if queue is empty we return an empty datablock
  if( prioQueue->isEmpty() )
  {
    message.clear();
    return message;
  }

  //get first datablock
  DataBlock_sPtr first_db = prioQueue->pop();
  dbStorage->remove( first_db->getHeader() );

  // compute first db length
  unsigned int msgLength = first_db->getLength().to_uint();

  ByteArray tmpContent;
  tmpContent.insert( first_db->getDataType() );
  tmpContent.append( first_db->getConfig() );
  tmpContent.append( first_db->getDataObjectID() );
  tmpContent.append( first_db->getSequenceNumber() );

  // length must for timestamp so we compute and add the bytes from the timestamp now
  unsigned int offset = (first_db->getConfig()[DB_CONFIG_TIMESTAMP_INDEX] == true) ? C_TIMESTAMP_BYTES : 0;
  tmpContent.append( first_db->getLength() + offset );

  if(first_db->getConfig()[DB_CONFIG_TIMESTAMP_INDEX] == true)
  {
    tmpContent.append( first_db->getTimestamp() );
    msgLength += C_TIMESTAMP_BYTES;
  }

  tmpContent.append(first_db->getContent()->dataPtr(), first_db->getContent()->size());

  // the timestamp bytes was handled in the smart prioritized Queue!
  // calculate message lengths to add maximal number of datablocks
  const std::size_t max_msg_length = (first_db->getLength().to_uint() > config->messageCrcBorder) ? MAX_MSG_LENGTH : config->messageCrcBorder;
  const std::size_t crc_length = (max_msg_length == MAX_MSG_LENGTH) ? MSG_CRC_32_BYTES : MSG_CRC_16_BYTES;
  const std::size_t message_header_length = MSG_FIXED_HEADER_LENGTH_BYTES + 2*MSG_ADDRESS_TYPE_IPV6_BYTES + crc_length;// + C_TIMESTAMP_BYTES;

  // pack more db to the message
  // cancel if there is no other datablocks or the message is to long
  while( !prioQueue->isEmpty() )
  {
    // avoid overflow; 1 to get not the first datablock in the queue but nothing -> we want to break the while loop in the next 5 lines
    const std::size_t free_space = (max_msg_length <= msgLength + message_header_length ) ? 1 : max_msg_length - msgLength - message_header_length;

    // get next datablock
    DataBlock_sPtr next_db = prioQueue->pop(free_space);
    if(next_db == nullptr) // no new db found
      break;

    dbStorage->remove( next_db->getHeader() );

    unsigned int tmp_length = next_db->getLength().to_uint();

    // insert header and content data
    tmpContent.append( next_db->getDataType() );
    tmpContent.append( next_db->getConfig() );
    tmpContent.append( next_db->getDataObjectID() );
    tmpContent.append( next_db->getSequenceNumber() );

    unsigned int offset = (first_db->getConfig()[DB_CONFIG_TIMESTAMP_INDEX] == true) ? C_TIMESTAMP_BYTES : 0;
    tmpContent.append( next_db->getLength() + offset );

    if(first_db->getConfig()[DB_CONFIG_TIMESTAMP_INDEX] == true)
    {
      tmpContent.append( first_db->getTimestamp() );
      msgLength += C_TIMESTAMP_BYTES;
    }
    tmpContent.append( next_db->getContent()->dataPtr(), next_db->getContent()->size());
    msgLength += tmp_length;
  }

  // compute message length
  MsgLength messageLength = msgLength + message_header_length;

  // append message header
  const MsgConfig msgConfig = config->messageConfig;
  const MsgSrcAddress srcAddr = ipv6StringToBin(config->currentIp); // TODO wir geben noch v4 addressen rein :D
  const MsgDstAddress dstAddr = ipv6StringToBin(config->ipAddress); // TODO wir geben noch v4 addressen rein :D

  message.insert(static_cast<MsgVersion>(VERSION_1) );
  message.append(msgConfig);
  message.append(srcAddr);
  message.append(dstAddr);
  message.append(messageLength);

  // append all datablocks
  message.append( tmpContent.dataPtr(), tmpContent.size() );

  //append crc
  if(messageLength >= config->messageCrcBorder)
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

