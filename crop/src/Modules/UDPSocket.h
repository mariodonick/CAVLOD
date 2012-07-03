/*
 * UDPSocket.h
 *
 *  Created on: 20.06.2012
 *      Author: mh447
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "NetworkIO.h"
#include "../Config.h"

class UDPSocket : public NetworkIO
{
public:
  UDPSocket();
  virtual ~UDPSocket();

private:
  const ByteArray* receiveData();
  void sendData(const ByteArray& data, const char* s_addr, const unsigned int& s_port);
  void startServer(const unsigned int& s_port);

private:
  int buflen;
  int sock_c, n_c;
  int sock_s, n_s;
  unsigned int length_c;
  int length_s;

  sockaddr_in server_c;
  sockaddr_in from_c;
  hostent *hp_c;

  socklen_t fromlen_s;
  sockaddr_in server_s;
  sockaddr_in from_s;

//  char buf_c;
  char buf_s[NETWORK_BUFFER_SIZE];
};

#endif /* UDPSOCKET_H_ */
