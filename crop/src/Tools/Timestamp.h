/*
 * @brief Timestamp.h
 *
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <sys/time.h>
#include <cstdint>

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

  void setTimestamp(const uint64_t& t)
  {
    curTime = t;
  }

  const uint64_t& getTime() const
  {
    return curTime;
  }

private:
  uint64_t curTime;
};

#endif /* TIMESTAMP_H_ */
