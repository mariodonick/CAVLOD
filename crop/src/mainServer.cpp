/*
 * @brief mainServer.cpp implementation of member functions
 */

#include "Modules/ReceiverModule.h"
#include "Tools/Log.h"
#include "DataManagement/CrodtIO.h"

#include <sys/signal.h>
#include <iostream>
#include <unistd.h>

#include "Tools/Bin.h"
#include "Tools/ByteArray.h"
#include "DataManagement/DataBlock.h"
#include "Modules/LocalStoreManager.h"

crodt::ReceiverModuleIF* receiver;

/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
void signal_handler_SIGINT (int status)
{
  std::cout << "*************       Received SIGINT signal. ********************\n";
  std::cout << "Info: Stopping Server Module\n";
  delete receiver; receiver = nullptr;
  INFO() << dbg::white << "Stopped  Server Module" << dbg::white << ENDL;

  exit(0);
}

void callbackFuntion(const crodt::CrodtOutput<std::string>& co)
{
    INFO() << co.sortedContent.content << ENDL;
}

void callbackFuntionSensor(const crodt::CrodtOutput<float>& co)
{
    INFO() << "value: " << co.sortedContent.content << ENDL;
    INFO() << "time: " << co.sortedContent.timestamp << ENDL;
}

int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  receiver = new crodt::ReceiverModule;
  receiver->start();
  crodt::TextCallback func = callbackFuntion;
  receiver->registerCallback(func);
  crodt::SensorCallback func2 = callbackFuntionSensor;
  receiver->registerCallback(func2);

  sleep(30000);

  return 0;
}
