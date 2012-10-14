/*
 * @brief CrodtModuleIF.h
 *
 */

#ifndef CRODTMODULEIF_H_
#define CRODTMODULEIF_H_

#include <string>

class CrodtModuleIF
{
public:
  virtual ~CrodtModuleIF(){}

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
  * param std::string text - this string includes the complete text (including all lines and  line breaks)
  * param bool timestamp - set this to true if you want to send the actual timestamp
  */
  virtual void sendText(const std::string& text, const bool& usingTimestamp) = 0;
};

#endif /* CRODTMODULEIF_H_ */
