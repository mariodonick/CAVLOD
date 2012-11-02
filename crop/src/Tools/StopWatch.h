/*
 * @brief StopWatch.h
 *
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <sys/time.h>
#include <iosfwd>

class StopWatch
{
public:
  StopWatch()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
  }

  virtual ~StopWatch()
  {
  }

  void restart()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
  }

  void start()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
  }

  void stop()
  {

    diff = (ts_end.tv_sec - ts_start.tv_sec) * 1e9 + ts_end.tv_nsec - ts_start.tv_nsec;
  }

  const double stopSec()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    return (ts_end.tv_sec - ts_start.tv_sec);
  }

  const double stopMsec()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    return (ts_end.tv_sec - ts_start.tv_sec) * 1e3 + (ts_end.tv_nsec - ts_start.tv_nsec) * 1e-6;
  }

  const double stopUsec()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    return (ts_end.tv_sec - ts_start.tv_sec) * 1e6 + (ts_end.tv_nsec - ts_start.tv_nsec) * 1e-3;
  }

  const double stopNsec()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    return (ts_end.tv_sec - ts_start.tv_sec) * 1e9 + (ts_end.tv_nsec - ts_start.tv_nsec);
  }

  friend std::ostream& operator<<(std::ostream& out, StopWatch& sw)
  {
    out << sw.stopNsec() << " ns";
    return out;
  }

  std::ostream& dumpMS(std::ostream& out)
  {
    return out << (ts_end.tv_sec - ts_start.tv_sec) * 1e3 + (ts_end.tv_nsec - ts_start.tv_nsec) * 1e-6 << " ms";
  }

  std::ostream& dumpUS(std::ostream& out)
  {
    return out << (ts_end.tv_sec - ts_start.tv_sec) * 1e6 + (ts_end.tv_nsec - ts_start.tv_nsec) * 1e-3 << " us";
  }

private:
  timespec ts_start, ts_end;
  double diff;
};

#endif /* STOPWATCH_H_ */
