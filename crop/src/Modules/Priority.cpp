/*
 * @brief Priority.cpp implementation of member functions
 */

#include "Priority.h"
#include "Crodm.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/Fifo.h"
#include "../Tools/Exception.h"
#include "../DataManagement/DataBlock.h"

#include <vector>

Priority::Priority(Queue<DataBlock*>& theDBFifo, Queue<DataBlock*>& thePrioQueue, const Crodm& theCrodm)
: dbFifo(theDBFifo)
, prioQueue(thePrioQueue)
, crodm(theCrodm)
{
}

Priority::~Priority()
{
}

void Priority::evaluate()
{
  const std::vector<float>* priorities = &crodm.getPriortyVec();

  cassert( priorities->size() >= dbFifo.size() );

  unsigned int i = 0;
  while( !dbFifo.isEmpty() )
  {
    DataBlock* data = dbFifo.pop();
    data->setPriority( (*priorities)[i] );
    prioQueue.push( data );
    ++i;
  }
}
