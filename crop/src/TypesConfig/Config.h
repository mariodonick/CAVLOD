/*
 * @brief Config.h - Singleton class to load configuration values
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

#include "../Tools/Bin.h"
#include "../TypesConfig/ProtocolTypes.h"

class Config
{
public:
  static Config* instance();
  static void release();

private:
  Config();
  virtual ~Config();
  Config(const Config&);
  Config& operator= (const Config&);

public:
  std::string homePath;
  std::string currentIp;
  //general
  unsigned int verbosity;
  std::string logPath;
  std::string backupPath;
  unsigned int port;
  std::string ipAddress;
  unsigned int sendDelayMS;
  unsigned int sensorInputDelayMS;
  //message
  std::size_t messageCrcBorder;
  MsgConfig messageConfig;

private:
  static Config* pInstance;
};

#endif /* CONFIG_H_ */
