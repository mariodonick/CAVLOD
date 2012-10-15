/*
 * MessagePacketizer.h
 *
 *  Created on: 04.06.2012
 *      Author: gigi
 */

#ifndef MESSAGEPACKETIZER_H_
#define MESSAGEPACKETIZER_H_

#include <string>
#include <iostream>
#include <sstream>

#include "Packetizer.h"
#include "../Tools/ByteArray.h"
#include "../Tools/Bin.h"
#include "../DataManagement/DataBlock.h"
#include "../TypesConfig/Pointer.h"

namespace crodt
{

class MessagePacketizer : public Packetizer
{
public:
  MessagePacketizer(DBQueue_uPtr& prioQueue, StoreManager_uPtr& storage);
  virtual ~MessagePacketizer();

private:
  const ByteArray& packetizeMessage();

  const MsgCrc32 computeCrc32();
  const MsgCrc16 computeCrc16();

private:
  DBQueue_uPtr& prioQueue;
  StoreManager_uPtr& dbStorage;
  ByteArray message;
};

} // namespace crodt

#endif /* MESSAGEPACKETIZER_H_ */
