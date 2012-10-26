/*
 * @brief ReceiverModule.h wrapper around receiver
 *
 */

#ifndef RECEIVERMODULE_H_
#define RECEIVERMODULE_H_

#include "ReceiverModuleIF.h"

namespace crodt
{

template<class T> class CrodtOutput;
class Receiver;

class ReceiverModule : public ReceiverModuleIF
{
public:
  ReceiverModule();
  virtual ~ReceiverModule();

  void start();
  void registerCallback(const TextCallback& cb);
  void registerCallback(const SensorCallback& cb);

private:
  Receiver* receiver;
};

}

#endif /* RECEIVERMODULE_H_ */
