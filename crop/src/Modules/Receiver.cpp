/*
 * @brief Receiver.cpp implementation of member functions
 */

#include "Receiver.h"
#include "UDPSocket.h"
#include "MessageParser.h"
#include "../TypesConfig/Config.h"

using namespace crodt;

Receiver::Receiver()
: network(new UDPSocket)
, parser(new MessageParser)
, running(true)
{

}

Receiver::~Receiver()
{
  running = false;
  Config::release();
}

void Receiver::start()
{
  receiverThread = std::thread(&Receiver::receivingLoop, this);
  INFO() << "Server initiated...\nWaiting for message..." << ENDL;
}

void Receiver::receivingLoop()
{
  while(running)
  {
    const ByteArray_sPtr arr = network->receiveData();
    parser->parse(*arr);
  }
}

void Receiver::registerCallback(const TextCallback& cb)
{
  parser->registerCallback(cb);
}

void Receiver::registerCallback(const SensorCallback& cb)
{
  parser->registerCallback(cb);
}
