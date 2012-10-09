/*
 * @brief Exception.h
 *
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <cassert>

inline void cassert(const bool& expression)
{
#ifdef DEBUG
  assert(expression);
#endif
}

#endif /* EXCEPTION_H_ */
