/*
 * @brief Decoder.h
 *
 */

#ifndef DECODER_H_
#define DECODER_H_

typedef unsigned int Doid;
typedef unsigned int SequenceNum;

template<class T>
class Decoder
{
protected:
  virtual ~Decoder(){}

  virtual void decode(const Doid& doid, const SequenceNum& seqNum, T* obj) = 0;
};

#endif /* DECODER_H_ */
