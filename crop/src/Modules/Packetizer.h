/*
 * packetizer.h
 *
 *  Created on: 04.06.2012
 *      Author: gigi
 */

#ifndef PACKETIZER_H_
#define PACKETIZER_H_

#include "../Tools/ByteArray.h"
#include "../DataManagement/DataBlock.h"

#include <string>
#include <sstream>

template<unsigned int> class Bin;

class Packetizer
{
public:
  virtual ~Packetizer(){}

  virtual ByteArray packetizeMessage() = 0;
};

#endif /* PACKETIZER_H_ */
