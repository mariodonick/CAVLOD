/*
 * @brief ServerModule.cpp implementation of member functions
 */

#include "ServerModule.h"
#include "MessageParser.h"
#include "UDPSocket.h"

ServerModule::ServerModule()
: network(new UDPSocket)
, parser(new MessageParser)
{
}

ServerModule::~ServerModule()
{
  delete parser;
  delete network;
}

void ServerModule::execute()
{
  while(true)
  {
    const ByteArray* arr = network->receiveData();
    parser->parse(*arr);
  }
}
