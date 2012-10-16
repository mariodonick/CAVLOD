/*
 * @brief ReceiverModuleIF.h
 *
 */

#ifndef RECEIVERMODULEIF_H_
#define RECEIVERMODULEIF_H_

#include <functional>
#include <string>

namespace crodt
{

template<class T> class CrodtOutput;

typedef const std::function<void(const CrodtOutput<std::string>)> TextCallback;
typedef const std::function<void(const CrodtOutput<float>)> SensorCallback;

class ReceiverModuleIF
{
public:
  virtual ~ReceiverModuleIF(){}

  /*
   * start the receiver nonblocking
   */
  virtual void start() = 0;

  /*
   * if this module received data it will send an callback which can you register here for text
   * * param TextCallback - the function which will be called
   */
  virtual void registerCallback(const TextCallback& cb) = 0;

  /*
   * if this module received data it will send an callback which can you register here for sensors
   * param SensorCallback - the function which will be called
   */
  virtual void registerCallback(const SensorCallback& cb) = 0;
};

} // namespace drodt

#endif /* RECEIVERMODULEIF_H_ */
