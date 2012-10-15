/*
 * @brief SenderModuleIF.h
 *
 */

#ifndef SENDERMODULEIF_H_
#define SENDERMODULEIF_H_

#include <string>

namespace crodt
{

struct CrodtInput;

class SenderModuleIF
{
public:
  virtual ~SenderModuleIF(){}

  /*
   * initialize the cordt module, call this first
   */
  virtual void initialize() = 0;

  /*
   * call this function to send sensor values to the crodt module
   * param float value - contain the next sensor value
   * param bool timestamp - set this to true if you want to send the actual timestamp
   */
  virtual void sendSensor(const float& value, const bool& usingTimestamp) = 0;

 /*
  * call this function to send a text to the crodt module
  * param std::string text - this string includes the complete text (including all lines and  line breaks)
  * param bool timestamp - set this to true if you want to send the actual timestamp
  */
  virtual void sendText(const std::string& text, const bool& usingTimestamp) = 0;

  /*
   * call this function to send a text to the crodt module with his own specific relevance data (used by gui)
   * param CrodtInput ci - includes all relevant data to split and send the content
   */
  virtual void sendText(const CrodtInput& ci) = 0;
};

} // namespace crodt

#endif /* SENDERMODULEIF_H_ */