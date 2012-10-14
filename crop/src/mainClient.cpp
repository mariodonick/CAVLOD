/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/ClientModule.h"
#include "Tools/Log.h"

#include <sys/signal.h>
#include <iostream>

ClientModule* client;

/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
void signal_handler_SIGINT (int status)
{
  std::cout << "*************       Received SIGINT signal. ********************\n";
  std::cout << "Info: Stopping Client Modul\n";
  delete client; client = nullptr;
  std::cout << "Info: Stopped  client Module\n";
  Config::release();
  exit(0);
}


int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  client = new ClientModule;
  client->initialize();
  client->run();

  while (true) sleep(300);
  return 0;
}
