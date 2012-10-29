/*
 * @brief SenderModule.cpp implementation of member functions
 */

#include "SenderModule.h"
#include "Sender.h"

using namespace crodt;

SenderModule::SenderModule()
: sender( new Sender)
{
}

SenderModule::~SenderModule()
{
  delete sender;
}

void SenderModule::initialize()
{
  sender->initialize();
}

void SenderModule::sendSensor(const float& value)
{
  sender->sendSensor(value);
}

void SenderModule::sendText(const std::string& text, const bool& usingTimestamp)
{
  sender->sendText(text, usingTimestamp);
}

void SenderModule::sendText(const CrodtInput& ci)
{
  sender->sendText(ci);
}
