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

template<class T>
class PrioritizedQueue;
class CombinedData;

class MessagePacketizer : public Packetizer
{
public:
  MessagePacketizer(PrioritizedQueue<CombinedData*>& prioQueue);
  virtual ~MessagePacketizer();

private:
  ByteArray packetizeMessage();

private:
  PrioritizedQueue<CombinedData*>& prioQueue;
  ByteArray message;
};

#endif /* MESSAGEPACKETIZER_H_ */
