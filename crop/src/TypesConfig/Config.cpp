/*
 * @brief Config.cpp implementation of member functions
 */

#include "Config.h"

Config* Config::pInstance = nullptr;

Config::Config()
: homePath( getenv("HOME") )
{
  try
  {
    boost::filesystem::path config_filename = homePath + "/CAVLOD/options.conf";
    boost::filesystem::path stdBackupPath = homePath + "/CAVLOD";
  //  boost::program_options::value<unsigned int>();//->default_value(0);

    boost::program_options::options_description my_options("options");

    my_options.add_options()
      ("General.backupPath", boost::program_options::value<boost::filesystem::path>()->default_value(stdBackupPath), "path to store datablocks")
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

    backupPath = vm["General.backupPath"].as<boost::filesystem::path>(); //todo pfad noch anlegen wenn er nicht existiert
    port = vm["General.port"].as<unsigned int>();
    ipAddress =  vm["General.ipAddress"].as<std::string>();
    sendDelayMS =  vm["General.sendDelayMS"].as<unsigned int>();
    sensorInputDelayMS =  vm["General.sensorInputDelayMS"].as<unsigned int>();

    if( !config_stream.is_open() )
      std::cout << "No \"options.conf\" file found, we will use the default options\n";
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
