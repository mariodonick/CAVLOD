/*
 * @brief ReceiverModule.h
 *
 */

#ifndef RECEIVERMODULE_H_
#define RECEIVERMODULE_H_

#include "../TypesConfig/Pointer.h"
#include "../DataManagement/DataTypes.h"
#include "MessageParser.h"

#include <thread>

namespace crodt
{

template<class T> class CrodtOutput;

class ReceiverModule
{
public:
  ReceiverModule();
  virtual ~ReceiverModule();

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
void ReceiverModule::registerCallback(const std::function<void(const CrodtOutput<T>&)>& cb, const DataTypes& dt)
{
  parser->registerCallback(cb, dt);
}

} // namespace crodt

#endif /* RECEIVERMODULE_H_ */
