/*
 * @brief SensorInput.cpp implementation of member functions
 */

#include "SensorInput.h"
#include "../TypesConfig/Config.h"

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
  Config* config = Config::instance();

  while(running)
  {
    usleep(config->sensorInputDelayMS * 1000);

    nextValue += 1;
    callback(id, true);
    id += 1;
  }
  std::cout << "sensor input thread finished" << std::endl;
}

const float& SensorInput::getInput()
{
  return nextValue;
}