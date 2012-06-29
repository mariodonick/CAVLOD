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

MessagePacketizer::MessagePacketizer(PrioritizedQueue& thePrioQueue)
: prioQueue(thePrioQueue)
{

}

MessagePacketizer::~MessagePacketizer()
{
}

ByteArray MessagePacketizer::packetizeMessage()
{
//  for(int i=0; i< prioQueue.size(); ++i)
//  {
//    ByteArray* db = prioQueue.pop();
//    message.append(db->dataPtr(), db->size());
//  }

  ByteArray* db = prioQueue.pop();
//  std::cout << "packetizer dump: \n";
//  db->dumpHex(std::cout);

  Bin<24> messageLength = MSG_FIXED_HEADER_LENGTH_BYTES + 2*MSG_ADDRESS_TYPE_IPV6_BYTES + db->size();

  message.insert(static_cast<Bin<4> >(VERSION_1) );
  message.append(MESSAGE_CONFIG); // todo message config genauer angeben
  message.append(SRC_ADDRESS);
  message.append(DST_ADDRESS);

  messageLength += (messageLength >= 0xFFFF) ? 4 : 2;

//  std::cout << "----------message packetizer complete message size: "  << messageLength.to_uint() << " \n";
//  std::cout << "----------message packetizer db size: "  << db->size() << " \n";
  message.append(messageLength);
//  std::cout << "----------message size packetize: "  << message.size() << " \n";
  message.append(db->dataPtr(), db->size());

  //message.append( (messageLength >= 0xFFFF) ? CRC_32 : CRC_16);

  if(messageLength >= 0xFFFF)
  {
    message.append(CRC_32);
  }
  else
  {
    message.append(CRC_16);
  }

//  message.dumpBin(std::cout);


  return message;
}
