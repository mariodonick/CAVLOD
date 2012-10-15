/*
 * @brief ReceiverModule.h
 *
 */

#ifndef RECEIVERMODULE_H_
#define RECEIVERMODULE_H_

#include "../DataManagement/DataTypes.h"
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
