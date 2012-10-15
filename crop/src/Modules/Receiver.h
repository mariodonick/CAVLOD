/*
 * @brief Receiver.h
 *
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "../TypesConfig/Pointer.h"
#include "../DataManagement/DataTypes.h"
#include "ReceiverModuleIF.h"

#include <thread>

namespace crodt
{

template<class T> class CrodtOutput;

class Receiver : public ReceiverModuleIF
{
public:
  Receiver();
  virtual ~Receiver();

  void start();

  void registerCallback(const TextCallback& cb);
  void registerCallback(const SensorCallback& cb);

private:
  void receivingLoop();

private:
  NetworkIO_uPtr network;
  Parser_uPtr parser;

  bool running;
  std::thread receiverThread;
};

} // namespace crodt

#endif /* RECEIVER_H_ */
