/*
 * @brief mainServer.cpp implementation of member functions
 */

#include "Modules/ServerModule.h"
#include "TypesConfig/Config.h"
#include "Tools/Log.h"

#include <sys/signal.h>
#include <iostream>
#include <unistd.h>

ServerModule* server;

/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
void signal_handler_SIGINT (int status)
{
  std::cout << "*************       Received SIGINT signal. ********************\n";
  std::cout << "Info: Stopping Server Modul\n";
  delete server; server = nullptr;
  INFO() << dbg::white << "Stopped  Server Module" << dbg::white << ENDL;
  exit(0);
}


int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  server = new ServerModule;
  server->start();

  Config::release();
  return 0;
}
