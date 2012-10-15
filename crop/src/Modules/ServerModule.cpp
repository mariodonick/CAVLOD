/*
 * @brief ServerModule.cpp implementation of member functions
 */

#include "ServerModule.h"
#include "UDPSocket.h"

ServerModule::ServerModule()
: network(new UDPSocket)
, parser(new MessageParser)
, running(true)
{

}

ServerModule::~ServerModule()
{
  running = false;
}

void ServerModule::start()
{
  receiverThread = std::thread(&ServerModule::receivingLoop, this);
  INFO() << "Server initiated...\nWaiting for message..." << ENDL;
}

void ServerModule::receivingLoop()
{
  while(running)
  {
    const ByteArray_sPtr arr = network->receiveData();
    parser->parse(*arr);
  }
}
