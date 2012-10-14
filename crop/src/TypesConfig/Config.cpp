/*
 * @brief Config.cpp implementation of member functions
 */

#include "Config.h"

#include <fstream>
#include <boost/program_options.hpp>

#include "../Tools/FileSystem.h"
#include "../Tools/IPTools.h"

Config* Config::pInstance = nullptr;

Config::Config()
: homePath( getenv("HOME") )
, currentIp( ownIP() )
{
  try
  {
    std::string config_filename = homePath + "/CAVLOD/options.conf";
    std::string stdPath = homePath + "/CAVLOD/";
    std::string stdBackupPath = stdPath + "backup/";

    boost::program_options::options_description my_options("options");

    my_options.add_options()
      ("General.backupPath", boost::program_options::value<std::string>()->default_value(stdBackupPath), "path to store datablocks")
      ("General.port", boost::program_options::value<unsigned int>()->default_value(5657), "port number")
      ("General.ipAddress", boost::program_options::value<std::string>()->default_value("127.0.0.1"), "IP Address for the receiver which get the message")
      ("General.sendDelayMS", boost::program_options::value<unsigned int>()->default_value(10000), "delay in ms to send a new message")
      ("General.sensorInputDelayMS", boost::program_options::value<unsigned int>()->default_value(1000), "delay in ms to create a new sensor value")

      ("Message.messageCrcBorder", boost::program_options::value<std::size_t>()->default_value(0xFFFF), "max size of the message for crc 16bit")
      ("Message.messageConfig", boost::program_options::value<unsigned int>()->default_value(0), "configuration bits for the message header")
    ;

    std::ifstream config_stream(config_filename.c_str());

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_config_file(config_stream, my_options), vm);
    boost::program_options::notify(vm);

    backupPath = vm["General.backupPath"].as<std::string>();
    port = vm["General.port"].as<unsigned int>();
    ipAddress = vm["General.ipAddress"].as<std::string>();
    sendDelayMS = vm["General.sendDelayMS"].as<unsigned int>();
    sensorInputDelayMS = vm["General.sensorInputDelayMS"].as<unsigned int>();
    messageCrcBorder = vm["Message.messageCrcBorder"].as<std::size_t>();
    messageConfig = vm["Message.messageConfig"].as<unsigned int>();

    // if '/' not exist append it, so you can insert folder and files easily
    if( backupPath.compare(backupPath.size()-1, 1, "/") != 0 ) // return 0 if '/' exists
      backupPath = backupPath +"/";

    // check if an options file exists
    if( !config_stream.is_open() )
      std::cout << "ERROR: file: \"options.conf\" not found, we will use the default options\n";

    // check if the backup path exists
    if( !existFolder(backupPath) )
    {
      if( backupPath.compare(stdBackupPath) == 0)
      {
        std::cout << "ERROR: Backup path does not exist - it will be created\n";
        createFolder(stdPath);
        createFolder(backupPath);
      }
      else
      {
        std::cout << "ERROR: Backup path does not exist, create it!\n";
        exit(1);
      }
    }
    else
    {
      std::cout << "ERROR: Backup path does not exist, create it!\n";
      exit(1);
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
