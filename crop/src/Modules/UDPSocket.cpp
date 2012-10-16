/*
 * UDPSocket.cpp
 *
 *  Created on: 20.06.2012
 *      Author: mh447
 */

#include "UDPSocket.h"
#include "../Tools/ByteArray.h"
#include "../Tools/Log.h"
#include "../TypesConfig/Config.h"

#include <string.h>

using namespace crodt;


UDPSocket::UDPSocket()
{
  Config* config = Config::instance();
  startServer(config->port);
}

UDPSocket::~UDPSocket()
{
	close(sock_c);
	close(sock_s);
}

const ByteArray_sPtr UDPSocket::receiveData()
{
  ByteArray_sPtr barr( new ByteArray );

  n_s = recvfrom(sock_s, &buf_s, NETWORK_BUFFER_SIZE, 0, (sockaddr *)&from_s, &fromlen_s);

  if(n_s < 0)
  {
    WARNING() << "error at receiving\n";
    return barr;
  }
  barr->insert(buf_s, n_s);

  return barr;
}

const bool UDPSocket::sendData(const ByteArray& data, const char* s_addr, const unsigned int& s_port)
{
	//open socket (SOCK_DGRAM = UDP Socket)
	sock_c = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_c < 0)
  {
	  perror("socket");
	  ERROR() << "socket" << ENDL;
	  close(sock_c);
	  return false;
  }

	server_c.sin_family = AF_INET;
	//hostname and address of the target server
	hp_c = gethostbyname(s_addr);
	if (hp_c==0)
	{
	  ERROR() << "Unknown host" << ENDL;
	  close(sock_c);
	  return false;
	}

	bcopy((char *)hp_c->h_addr,
		(char *)&server_c.sin_addr,
		 hp_c->h_length);

	//port of the target server
	server_c.sin_port = htons(s_port);

	length_c = sizeof(struct sockaddr_in);

	//send message to the server with the chosen address and port
	n_c = sendto(sock_c, data.dataPtr(), data.size(), 0 ,(sockaddr *)&server_c,length_c);

	if (n_c < 0)
	{
	  ERROR() << "error by sending\n";
	  close(sock_c);
	  return false;
	}

	close(sock_c);
	return true;
}

void UDPSocket::startServer(const unsigned int& s_port)
{
	//Inet Socket, SOCK_DGRAM = UDP Socket
	sock_s = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock_s < 0) INFO() << ("Opening socket") << ENDL;

	length_s = sizeof(server_s);
	bzero(&server_s,length_s);
	server_s.sin_family=AF_INET;

	//address of the server
	server_s.sin_addr.s_addr = INADDR_ANY;

	//port from the server
	server_s.sin_port = htons(s_port);

	//assign port and address to server
	if( ::bind(sock_s, (struct sockaddr *) &server_s, length_s) < 0 )
	  DBG() << "binding port and address to server" << ENDL;

	fromlen_s = sizeof(struct sockaddr_in);
}
