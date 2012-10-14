/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/CrodtModule.h"
//#include "Tools/Log.h"
//
//#include <sys/signal.h>
//#include <iostream>



/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
//void signal_handler_SIGINT (int status)
//{
//  std::cout << "*************       Received SIGINT signal. ********************\n";
//  std::cout << "Info: Stopping Client Modul\n";
//  delete crodt; crodt = nullptr;
//  INFO() << dbg::white << "Stopped  Server Module" << dbg::white << ENDL;
//  Config::release();
//  exit(0);
//}


int main()
{
  CrodtModuleIF* crodt = new CrodtModule;

  crodt->initialize();
  crodt->sendText("hallo welt", true);

  delete crodt;
  return 0;
}
