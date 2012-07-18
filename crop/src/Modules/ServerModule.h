/*
 * @brief ServerModule.h
 *
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

#include "../TypesConfig/Pointer.h"

class ServerModule
{
public:
  ServerModule();
  virtual ~ServerModule();

  void start();

private:
  NetworkIO_uPtr network;
  Parser_uPtr parser;

  bool running;
};

#endif /* SERVERMODULE_H_ */
