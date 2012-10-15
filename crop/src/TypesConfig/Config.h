/*
 * @brief Config.h - Singleton class to load configuration values
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

#include "../Tools/Bin.h"
#include "../TypesConfig/ProtocolTypes.h"

namespace crodt
{

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

} // namespace crodt

#endif /* CONFIG_H_ */
