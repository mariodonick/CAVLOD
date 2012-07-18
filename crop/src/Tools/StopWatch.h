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
    return (ts_end.tv_sec - ts_start.tv_sec) * 1e9 + (ts_end.tv_nsec - ts_start.tv_nsec) * 1e3;
  }

  const double stopUsec()
  {
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    return (ts_end.tv_sec - ts_start.tv_sec) * 1e9 + (ts_end.tv_nsec - ts_start.tv_nsec) * 1e6;
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

private:
  timespec ts_start, ts_end;
  double diff;
};

//  float a = 23.2;
//  float b = 2.23423;
//  struct timespec ts_res, ts_start, ts_end;
//  clock_getres(CLOCK_MONOTONIC, &ts_res);
//
//  std::cout << "Resolution: " << ts_res.tv_sec << " and " << ts_res.tv_nsec << std::endl;
//
//  int i = 0;
//  clock_gettime(CLOCK_MONOTONIC, &ts_start);
//  //do something: ....
//  while(i < 1000)
//  {
//    if(a < b)
//      a=2;
//    i++;
//  }
//  clock_gettime(CLOCK_MONOTONIC, &ts_end);
//  std::cout << "i: " << i << std::endl;
//  std::cout << "Elapsed time:"  << ((ts_end.tv_sec - ts_start.tv_sec) * 1000000000 + ts_end.tv_nsec - ts_start.tv_nsec) << "ns"<< std::endl;



#endif /* STOPWATCH_H_ */
