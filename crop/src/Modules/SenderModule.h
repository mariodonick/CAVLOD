/*
 * @brief SenderModule.h wrapper around sender
 *
 */

#ifndef SENDERMODULE_H_
#define SENDERMODULE_H_

#include "SenderModuleIF.h"

namespace crodt
{

class SenderModule : public SenderModuleIF
{
public:
  SenderModule();
  virtual ~SenderModule();

  void initialize();
  void sendSensor(const float& value);
  void sendText(const std::string& text, const bool& usingTimestamp);
  void sendText(const CrodtInput& ci);

private:

  SenderModuleIF* sender;
};

}

#endif /* SENDERMODULE_H_ */
