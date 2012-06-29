/*
 * @brief ServerModule.h
 *
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

class Parser;
class NetworkIO;

class ServerModule
{
public:
  ServerModule();
  virtual ~ServerModule();

  void execute();

private:
  NetworkIO* network;
  Parser* parser;
};

#endif /* SERVERMODULE_H_ */
