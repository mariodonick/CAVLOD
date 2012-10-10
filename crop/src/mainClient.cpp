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

#include "TypesConfig/Config.h"

int main()
{
//  signal(SIGINT, signal_handler_SIGINT);
//
//  client = new ClientModule;
//  client->start();
//
//  while (true) sleep(300);




  // ordner erstellen mit c
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <dirent.h> //eventl weg
//#include <sys/stat.h> //eventl weg
//#include <cstring> //eventl weg
//
//  using namespace std;
//  string artist = "test";
//  string directory = "/home/flo/";
//
//  if(chdir(directory.c_str()) == -1) {
//    cerr << "Fehler in chdir: " << strerror(errno) << endl;
//  }
//  else if(mkdir(artist.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
//  {
//      cerr << "Fehler in mkdir: " << strerror(errno) << endl;
//  }

  Config* config = Config::instance();

  boost::filesystem::path p("/CAVLOD");
  boost::filesystem::path home = getenv("HOME");
  boost::filesystem::path path = home;
  path /= p;
  std::cout << home << std::endl;
  std::cout << p << std::endl;
  std::cout << path << std::endl;

  boost::filesystem::file_status s = boost::filesystem::status(p);
  std::cout << boost::filesystem::is_directory(s) << std::endl;

  std::cout << p.root_name() << std::endl;
  std::cout << p.root_directory() << std::endl;
  std::cout << p.root_path() << std::endl;
  std::cout << p.relative_path() << std::endl;
  std::cout << p.parent_path() << std::endl;
  std::cout << p.filename() << std::endl;

  return 0;
}
