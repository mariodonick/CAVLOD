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

typedef const std::function<void(const CrodtOutput<std::string>&)> TextCallback;
typedef const std::function<void(const CrodtOutput<float>&)> SensorCallback;

class ReceiverModuleIF
{
public:
  virtual ~ReceiverModuleIF(){}

  virtual void start() = 0;
  virtual void registerCallback(const TextCallback& cb) = 0;
  virtual void registerCallback(const SensorCallback& cb) = 0;
};

} // namespace drodt

#endif /* RECEIVERMODULEIF_H_ */
