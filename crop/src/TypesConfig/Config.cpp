/*
 * @brief Config.cpp implementation of member functions
 */

#include "Config.h"

#include <fstream>
#include <boost/program_options.hpp>

#include "../Tools/FileSystem.h"

Config* Config::pInstance = nullptr;

Config::Config()
: homePath( getenv("HOME") )
{
  try
  {
    std::string config_filename = homePath + "/CAVLOD/options.conf";
    std::string stdBackupPath = homePath + "/CAVLOD";
  //  boost::program_options::value<unsigned int>();//->default_value(0);

    boost::program_options::options_description my_options("options");

    my_options.add_options()
      ("General.backupPath", boost::program_options::value<std::string>()->default_value(stdBackupPath), "path to store datablocks")
      ("General.port", boost::program_options::value<unsigned int>()->default_value(5657), "port number")
      ("General.ipAddress", boost::program_options::value<std::string>()->default_value("localhost"), "IP Address for the receiver which get the message")
      ("General.sendDelayMS", boost::program_options::value<unsigned int>()->default_value(10000), "delay in ms to send a new message")
      ("General.sensorInputDelayMS", boost::program_options::value<unsigned int>()->default_value(1000), "delay in ms to create a new sensor value")
    ;

    std::ifstream config_stream(config_filename.c_str());

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_config_file(config_stream, my_options), vm);
    boost::program_options::notify(vm);
    // value is now accessible by vm["SectionName.my_opt"].as<int>()

    backupPath = vm["General.backupPath"].as<std::string>(); //todo pfad noch anlegen wenn er nicht existiert
    port = vm["General.port"].as<unsigned int>();
    ipAddress =  vm["General.ipAddress"].as<std::string>();
    sendDelayMS =  vm["General.sendDelayMS"].as<unsigned int>();
    sensorInputDelayMS =  vm["General.sensorInputDelayMS"].as<unsigned int>();

    if( !config_stream.is_open() )
      std::cout << "file: \"options.conf\" not found, we will use the default options\n";

    if( !existFolder(backupPath) )
    {
      createFolder(backupPath);
      std::cout << "Backup path does not exist - it will be created\n";
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

Config::~Config()
{

}

Config* Config::instance()
{
  if( pInstance == nullptr )
    pInstance = new Config();
  return pInstance;
}

void Config::release()
{
  if( pInstance != nullptr )
    delete pInstance;
  pInstance = nullptr;
}
