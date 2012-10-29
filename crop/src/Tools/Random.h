/**
 * @brief Random.h
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include <ctime>
#include <cmath>

inline double randomDouble(const double& start = 0.0, const double& end = 1.0)
{
  return start +( ( std::rand()/static_cast<double>(RAND_MAX) ) * (end - start) );
}

inline int randomInt(const int& start = 0, const int& end = 1)
{
  return( start + std::rand() % (end - start + 1) );
}

inline void randomInitialize()
{
  static bool already_initialized = false;
  if(!already_initialized)
  {
    std::srand(static_cast<unsigned>(std::time(0)));
    already_initialized=true;
  }
}

// return a normal distributedn random value
// m = mean s = sigma standard deviation: N(my,sigma)
inline double normalDist(const double& mean, const double& sigma)
{
  double x1, x2, w, y1;
  static double y2;
  static int use_last = 0;

  if (use_last)
  {
    y1 = y2;
    use_last = 0;
  }
  else
  {
    do
    {
      x1 = 2.0 * randomDouble() - 1.0;
      x2 = 2.0 * randomDouble() - 1.0;
      w = x1 * x1 + x2 * x2;
    }
    while (w >= 1.0);

    w = std::sqrt((-2.0 * std::log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;
    use_last = 1;
  }
  return mean + y1 * sigma;
}

#endif /* RANDOM_H_ */
