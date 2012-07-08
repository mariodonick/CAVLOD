/*
 * @brief ServerModule.cpp implementation of member functions
 */

#include "ServerModule.h"
#include "MessageParser.h"
#include "UDPSocket.h"

ServerModule::ServerModule()
: network(new UDPSocket)
, parser(new MessageParser)
, running(false)
{
  running = true;
  std::clog << "Server initiated...\nWaiting for message...\n";
}

ServerModule::~ServerModule()
{
  running = false;

  delete parser;
  delete network;
}

void ServerModule::execute()
{
  while(running)
  {
    const ByteArray* arr = network->receiveData();
    parser->parse(*arr);
  }
}
