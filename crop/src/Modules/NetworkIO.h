/*
 * @brief NetworkIO.h
 *
 */

#ifndef NETWORKIO_H_
#define NETWORKIO_H_

class ByteArray;

class NetworkIO
{
public:
  virtual ~NetworkIO(){}

  virtual const ByteArray* receiveData() = 0;
  virtual void sendData(const ByteArray& data, const char* s_addr, const unsigned int& s_port) = 0;
};

#endif /* NETWORKIO_H_ */
