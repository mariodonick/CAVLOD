/*
 * @brief Config.h - Singleton class to load configuration values
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

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
  std::string backupPath;

  unsigned int port;
  std::string ipAddress;

  unsigned int sendDelayMS;
  unsigned int sensorInputDelayMS;

private:
  static Config* pInstance;
};

#endif /* CONFIG_H_ */
