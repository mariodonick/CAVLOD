/*
 * @brief ContentProcess.h
 *
 */

#ifndef CONTENTPROCESS_H_
#define CONTENTPROCESS_H_

#include "CrodtIO.h"

namespace crodt
{

template<class T>
struct ContentProcess
{
  T content;
  Position pos;
  std::size_t size;
};

} // namespace crodt

#endif /* CONTENTPROCESS_H_ */
