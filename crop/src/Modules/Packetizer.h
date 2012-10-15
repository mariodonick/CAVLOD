/*
 * packetizer.h
 *
 *  Created on: 04.06.2012
 *      Author: gigi
 */

#ifndef PACKETIZER_H_
#define PACKETIZER_H_

#include "../DataManagement/DataBlock.h"

class ByteArray;

namespace crodt
{

class Packetizer
{
public:
  virtual ~Packetizer(){}

  virtual const ByteArray& packetizeMessage() = 0;
};

} // namespace crodt

#endif /* PACKETIZER_H_ */
