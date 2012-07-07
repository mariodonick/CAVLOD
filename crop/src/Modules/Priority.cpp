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

Priority::Priority(Queue<DataBlock*>& theFifo, PrioritizedQueue<DataBlock*>& thePrioQueue, const Ontology& theOntology)
: fifo(theFifo)
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

  assert( priorities->size() >= fifo.size() );

  unsigned int i = 0;
  while( !fifo.isEmpty() )
  {
    DataBlock* data = fifo.pop();
    data->setPriority( (*priorities)[i] );
    prioQueue.push( data );
    ++i;
  }
}
