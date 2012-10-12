/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/ClientModule.h"

#include <sys/signal.h>
#include <iostream>
//#include <vector>

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
  exit(0);
}


#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>
#include "Tools/FileSystem.h"

#include "TypesConfig/Config.h"

int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  client = new ClientModule;
  client->initialize();
  client->run();

  while (true) sleep(300);
  return 0;
}
