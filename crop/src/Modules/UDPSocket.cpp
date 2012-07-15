/*
 * UDPSocket.cpp
 *
 *  Created on: 20.06.2012
 *      Author: mh447
 */

#include "UDPSocket.h"
#include "../Tools/ByteArray.h"

#include <string.h>
#include <iostream>

using namespace std;

UDPSocket::UDPSocket()
{
  startServer(PORT);
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

  std::cout << "received length: " << n_s << "\n";
  if(n_s < 0)
  {
    std::cout << "fehler beim empfangen\n";
    return barr;
  }
  barr->insert(buf_s, n_s);

  return barr;
}

void UDPSocket::sendData(const ByteArray& data, const char* s_addr, const unsigned int& s_port)
{
	//Socket oeffnen (SOCK_DGRAM = UDP Socket)
	sock_c= socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_c < 0) cout << "socket" << endl;

	server_c.sin_family = AF_INET;
	//Hostname bzw. Adresse des Zielservers
	hp_c = gethostbyname(s_addr);
	if (hp_c==0) cout << "Unknown host" << endl;

	bcopy((char *)hp_c->h_addr,
		(char *)&server_c.sin_addr,
		 hp_c->h_length);

	//Port des Zielservers
	server_c.sin_port = htons(s_port);

	length_c = sizeof(struct sockaddr_in);

	//Nachricht an Server mit angegebener Adresse und angegebenem Port senden
	n_c=sendto(sock_c, data.dataPtr(), data.size(), 0 ,(sockaddr *)&server_c,length_c);

	if (n_c < 0)
	  std::cout << "fehler beim senden\n";

	//	n = recvfrom(sock_c,&buf_c,buflen,0,(struct sockaddr *)&from_c, &length_c);
	//	write(1,&buf_c,n_c);
	//close(sock_c);
	close(sock_c);
}

void UDPSocket::startServer(const unsigned int& s_port)
{
	//Inet Socket, SOCK_DGRAM = UDP Socket
	sock_s=socket(AF_INET, SOCK_DGRAM, 0);

	if (sock_s < 0) cout << ("Opening socket") << endl;

	length_s = sizeof(server_s);
	bzero(&server_s,length_s);
	server_s.sin_family=AF_INET;

	//Adresse des Servers
	server_s.sin_addr.s_addr = INADDR_ANY;

	//Port des Servers
	server_s.sin_port = htons(s_port);

	//Port und adresse des Servers werden dem Socket zugewiesen
	if( ::bind(sock_s, (struct sockaddr *) &server_s, length_s) < 0 )
	  cout << "binding" << endl;

	fromlen_s = sizeof(struct sockaddr_in);
}

