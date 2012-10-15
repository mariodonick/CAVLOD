/*
 * @brief mainServer.cpp implementation of member functions
 */

#include "Modules/ServerModule.h"
#include "TypesConfig/Config.h"

#include <sys/signal.h>
#include <iostream>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <string>
#include <vector>
#include <sstream>


ServerModule* server;

/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
void signal_handler_SIGINT (int status)
{
  std::cout << "*************       Received SIGINT signal. ********************\n";
  std::cout << "Info: Stopping Server Modul\n";
  delete server; server = nullptr;
  std::cout << "Info: Stopped  Server Module\n";
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
