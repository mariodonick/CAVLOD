/*
 * @brief SensorInput.h
 *
 */

#ifndef SENSORINPUT_H_
#define SENSORINPUT_H_

#include "ContentInput.h"

class SensorInput : public ContentInput<float>, public ContentThreadModule
{
public:
  SensorInput(const bool& running, const ReadyCallback& function);
  virtual ~SensorInput();

private:
  void run();
  const float& getInput();

private:
  float nextValue;
};

#endif /* SENSORINPUT_H_ */
