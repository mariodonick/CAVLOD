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
  std::cout << "Info: Stopping Server Module\n";
  delete server; server = nullptr;
  INFO() << dbg::white << "Stopped  Server Module" << dbg::white << ENDL;

  exit(0);
}

void callbackFuntion(const CrodtOutput<std::string>& co)
{
  DBG() << "CAAAAAAAAAAAALLLLLLLLLLLLBBBBBBBBBBBBAAAAAAAACCCCCCCKKKKKKKKKKKKKK" << ENDL;
  std::vector<COItem<std::string> >::const_iterator it = co.sortedContent.begin();
  for(; it != co.sortedContent.end(); ++it)
    DBG() << it->content;
}

int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  server = new ServerModule;
  server->start();
  std::function<void(const CrodtOutput<std::string>&)> func = callbackFuntion;
  server->registerCallback(func, TYPE_TEXT);

  sleep(30);
  return 0;
}
