/*
 * @brief ReceiverModule.cpp implementation of member functions
 */

#include "ReceiverModule.h"
#include "UDPSocket.h"
#include "../TypesConfig/Config.h"

using namespace crodt;

ReceiverModule::ReceiverModule()
: network(new UDPSocket)
, parser(new MessageParser)
, running(true)
{

}

ReceiverModule::~ReceiverModule()
{
  running = false;
  Config::release();
}

void ReceiverModule::start()
{
  receiverThread = std::thread(&ReceiverModule::receivingLoop, this);
  INFO() << "Server initiated...\nWaiting for message..." << ENDL;
}

void ReceiverModule::receivingLoop()
{
  while(running)
  {
    const ByteArray_sPtr arr = network->receiveData();
    parser->parse(*arr);
  }
}
