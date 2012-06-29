/*
 * @brief SplitEncoding.h
 *
 */

#ifndef SPLITENCODING_H_
#define SPLITENCODING_H_

#include "Partitioning.h"

class Ontology;
template<class T> class Queue;
class ByteArray;

class SplitEncoding : public Partitioning
{
public:
  SplitEncoding(const Ontology& ontology, Queue<ByteArray*>& queue);
  virtual ~SplitEncoding();

private:
  void partText(const Bin<24>& doid, const std::string& content);
  void partSensor(const Bin<24>& doid, const float& value);

private:
  const Ontology& ontology;
  Queue<ByteArray*>& queue;
};

#endif /* SPLITENCODING_H_ */
