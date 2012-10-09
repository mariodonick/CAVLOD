/*
 * @brief Timestamp.h
 *
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <sys/time.h>
#include <cstdint>

#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Bin.h"

class Timestamp
{
public:
  Timestamp()
  : curTime(0)
  {
  }

  virtual ~Timestamp(){}

  void stamp()
  {
    timeval t;
    gettimeofday(&t, 0);
    curTime = t.tv_sec;
  }

  void setTimestamp(const CTimestamp& t)
  {
    curTime = t;
  }

  const CTimestamp& getTime() const
  {
    return curTime;
  }

private:
  CTimestamp curTime;
};

#endif /* TIMESTAMP_H_ */
