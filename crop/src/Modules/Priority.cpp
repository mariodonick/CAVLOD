/*
 * @brief Priority.cpp implementation of member functions
 */

#include "Priority.h"
#include "Ontology.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/Fifo.h"
#include "../DataManagement/DataBlock.h"

#include <cassert>
#include <vector>

Priority::Priority(Queue<DataBlock*>& theDBFifo, PrioritizedQueue<DataBlock*>& thePrioQueue, const Ontology& theOntology)
: dbFifo(theDBFifo)
, prioQueue(thePrioQueue)
, ontology(theOntology)
{
}

Priority::~Priority()
{
}

void Priority::evaluate()
{
  const std::vector<float>* priorities = &ontology.getPriortyVec();

  assert( priorities->size() >= dbFifo.size() );

  unsigned int i = 0;
  while( !dbFifo.isEmpty() )
  {
    DataBlock* data = dbFifo.pop();
    data->setPriority( (*priorities)[i] );
    prioQueue.push( data );
    ++i;
  }
}
