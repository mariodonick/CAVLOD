/*
 * @brief mainServer.cpp implementation of member functions
 */

#include "Modules/ReceiverModule.h"
#include "Tools/Log.h"
#include "DataManagement/CrodtIO.h"

#include <sys/signal.h>
#include <iostream>
#include <unistd.h>


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
  std::vector<crodt::COItem<std::string> >::const_iterator it = co.sortedContent.begin();
  for(; it != co.sortedContent.end(); ++it)
    DBG() << it->content;
}

int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  receiver = new crodt::ReceiverModule;
  receiver->start();
  crodt::TextCallback func = callbackFuntion;
  receiver->registerCallback(func);

  sleep(300);

  return 0;
}
