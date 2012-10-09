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
}

void ServerModule::start()
{
  while(running)
  {
    const ByteArray_sPtr arr = network->receiveData();
    parser->parse(*arr);
  }
}
