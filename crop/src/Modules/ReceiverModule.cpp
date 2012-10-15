/*
 * @brief ReceiverModule.cpp implementation of member functions
 */

#include "ReceiverModule.h"
#include "Receiver.h"

using namespace crodt;


ReceiverModule::ReceiverModule()
: receiver(new Receiver)
{

}

ReceiverModule::~ReceiverModule()
{
  delete receiver;
}

void ReceiverModule::start()
{
  receiver->start();
}

void ReceiverModule::registerCallback(const std::function<void(const CrodtOutput<std::string>&)>& cb)
{
  receiver->registerCallback(cb);
}

void ReceiverModule::registerCallback(const std::function<void(const CrodtOutput<float>&)>& cb)
{
  receiver->registerCallback(cb);
}
