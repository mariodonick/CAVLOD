/*
 * @brief Priority.cpp implementation of member functions
 */

#include "Priority.h"
#include "Crodm.h"
#include "LocalStoreManager.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/Fifo.h"
#include "../DataManagement/DataBlock.h"

#include <vector>

Priority::Priority(
    DBQueue_uPtr& theDBFifo,
    DBQueue_uPtr& thePrioQueue,
    const Crodm_uPtr& theCrodm,
    StoreManager_uPtr& storage)
: dbFifo(theDBFifo)
, prioQueue(thePrioQueue)
, crodm(theCrodm)
, dbStorage(storage)
{
}

Priority::~Priority()
{
}

void Priority::evaluate()
{
  unsigned int i = 0;
  while( !dbFifo->isEmpty() )
  {
    DataBlock_sPtr data = dbFifo->pop();

    const float& prio = crodm->getPriority( data->getRelevanceData(),
                                            data->getDataObjectID(),
                                            data->getDataType() );
    data->setPriority( prio );
    prioQueue->push( data );
    dbStorage->store(data);
//    dbStorage->remove( data->getDataObjectID(), data->getSequenceNumber() );
    ++i;
  }
}
