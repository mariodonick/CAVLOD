/*
 * @brief SensorInput.cpp implementation of member functions
 */

#include "SensorInput.h"

#include <iostream>

SensorInput::SensorInput(const bool& running, const ReadyCallback& function)
: ContentThreadModule(running, function)
, nextValue(0.f)
{
}

SensorInput::~SensorInput()
{
}

void SensorInput::run()
{
  while(running)
  {
    sleep(1);

    nextValue += 1;
    callback(id);
    id += 1;
  }
  std::cout << "sensor input thread finished" << std::endl;
}

const float& SensorInput::getInput()
{
  return nextValue;
}
