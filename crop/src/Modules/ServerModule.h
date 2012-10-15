/*
 * @brief ServerModule.h
 *
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

#include "../TypesConfig/Pointer.h"
#include "../DataManagement/DataTypes.h"
#include "MessageParser.h"

#include <thread>

template<class T> class CrodtOutput;

class ServerModule
{
public:
  ServerModule();
  virtual ~ServerModule();

  void start();

  template<class T>
  void registerCallback(const std::function<void(const CrodtOutput<T>&)>& cb, const DataTypes& dt);

private:
  void receivingLoop();

private:
  NetworkIO_uPtr network;
  Parser_uPtr parser;

  bool running;
  std::thread receiverThread;
};


template<class T>
void ServerModule::registerCallback(const std::function<void(const CrodtOutput<T>&)>& cb, const DataTypes& dt)
{
  parser->registerCallback(cb, dt);
}

#endif /* SERVERMODULE_H_ */
