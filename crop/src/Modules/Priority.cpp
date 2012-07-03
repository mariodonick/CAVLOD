/*
 * @brief Priority.cpp implementation of member functions
 */

#include "Priority.h"
#include "Ontology.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/Fifo.h"
#include "../DataClasses/InterModuleData.h"

#include <cassert>
#include <vector>

Priority::Priority(Queue<ByteArray*>& theFifo, PrioritizedQueue<PrioQueueData*>& thePrioQueue, const Ontology& theOntology)
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
    PrioQueueData* data = new PrioQueueData; // todo löschen????
    data->content = fifo.pop();
    data->priority = (*priorities)[i];
    prioQueue.push( data );
    ++i;
  }
}
