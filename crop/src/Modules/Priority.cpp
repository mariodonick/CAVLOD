/*
 * @brief Priority.cpp implementation of member functions
 */

#include "Priority.h"
#include "Ontology.h"
#include "../Tools/PrioritizedQueue.h"
#include "../Tools/Fifo.h"
#include "../DataManagement/CombinedData.h"

#include <cassert>
#include <vector>

Priority::Priority(Queue<ByteArray*>& theFifo, PrioritizedQueue<CombinedData*>& thePrioQueue, const Ontology& theOntology)
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
    CombinedData* data = new CombinedData; // todo WO löschen????
    data->content = fifo.pop();
    data->priority = (*priorities)[i];
    prioQueue.push( data );
    ++i;
  }
}
