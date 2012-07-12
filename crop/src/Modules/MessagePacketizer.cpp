/*
 * packatizer.cpp
 *
 *  Created on: 04.06.2012
 *      Author: gigi
 */

#include "MessagePacketizer.h"
#include "../Config.h"
#include "../Types.h"
#include "../Tools/PrioritizedQueue.h"
#include "../DataManagement/DataBlock.h"

MessagePacketizer::MessagePacketizer(Queue<DataBlock*>& thePrioQueue)
: prioQueue(thePrioQueue)
{

}

MessagePacketizer::~MessagePacketizer()
{
}

// if the fifo is empty this function return a empty bytearray
// otherwise this return the current message
const ByteArray& MessagePacketizer::packetizeMessage()
{
//  for(int i=0; i< prioQueue.size(); ++i)
//  {
//    ByteArray* db = prioQueue.pop();
//    message.append(db->dataPtr(), db->size());
//  }


  // if queue is empty we return an empty datablock
  if( prioQueue.isEmpty() )
  {
    message.clear();
    return message;
  }

  //get next datablock
  DataBlock* data = prioQueue.pop();

  // compute db length
  unsigned int dbLength = data->getLength().to_uint();

  // compute message length
  Bin<24> messageLength = dbLength + MSG_FIXED_HEADER_LENGTH_BYTES + 2*MSG_ADDRESS_TYPE_IPV6_BYTES;
  messageLength += (messageLength >= 0xFFFF) ? 4 : 2;

  // append message header
  message.insert(static_cast<Bin<4> >(VERSION_1) );
  message.append(MESSAGE_CONFIG); // todo message config genauer angeben/ iwo auslesen
  message.append(SRC_ADDRESS);
  message.append(DST_ADDRESS);
  message.append(messageLength);

  // append datablock header
  message.append( data->getDataType() );
  message.append( data->getConfig() );
  message.append( data->getDataObjectID() );
  message.append( data->getSequenceNumber() );
  message.append( Bin<16>( dbLength ) );

  // append datablock content
  message.append(data->getContent()->dataPtr(), data->getContent()->size());

  //append crc
  if(messageLength >= 0xFFFF)
  {
    message.append(CRC_32);
  }
  else
  {
    message.append(CRC_16);
  }

  return message;
}
