/*
 * @brief ContentInput.h
 *
 */

#ifndef CONTENTINPUT_H_
#define CONTENTINPUT_H_

#include <functional>
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Bin.h"

typedef std::function<void(const DBDataObjectID&, const bool&)> ReadyCallback;

template<class T>
class ContentInput
{
public:
  virtual ~ContentInput(){}

  virtual const T& getInput() = 0;
  virtual void run() = 0;
};


class ContentThreadModule
{
protected:
  ContentThreadModule(const bool& run, const ReadyCallback& cb)
  : running(run)
  , callback(cb)
  , id(0)
  {

  }

  virtual ~ContentThreadModule()
  {

  }
protected:
  const bool& running;
  ReadyCallback callback;
  DBDataObjectID id;
};


#endif /* CONTENTINPUT_H_ */
