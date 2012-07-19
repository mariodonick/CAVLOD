/*
 * @brief Priority.h
 *
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "Prioritization.h"
#include "../TypesConfig/Pointer.h"

class Priority : public Prioritization
{
public:
  Priority(DBQueue_uPtr& theFifo, DBQueue_uPtr& thePrioQueue, const Crodm_uPtr& crodm);
  virtual ~Priority();

private:
  void evaluate();

private:
  DBQueue_uPtr& dbFifo;
  DBQueue_uPtr& prioQueue;
  const Crodm_uPtr& crodm;
};

#endif /* PRIORITY_H_ */
