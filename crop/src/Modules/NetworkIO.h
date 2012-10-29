/*
 * @brief NetworkIO.h
 *
 */

#ifndef NETWORKIO_H_
#define NETWORKIO_H_

#include "../TypesConfig/Pointer.h"

namespace crodt
{

class NetworkIO
{
public:
  virtual ~NetworkIO(){}

  virtual const ByteArray_sPtr receiveData() = 0;
  virtual const bool sendData(const ByteArray& data, const char* s_addr, const unsigned int& s_port) = 0;
  virtual void startServer(const unsigned int& s_port) = 0;
};

} // namespace crodt

#endif /* NETWORKIO_H_ */
