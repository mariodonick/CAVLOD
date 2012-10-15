/*
 * @brief Decoder.h
 *
 */

#ifndef DECODER_H_
#define DECODER_H_

#include "../TypesConfig/ProtocolTypes.h"

namespace crodt
{

template<class T>
class Decoder
{
protected:
  virtual ~Decoder(){}

  virtual void decode(const DBDataObjectID& doid, const DBSequenceNumber& seqNum, T obj) = 0;
};

} // namespace crodt

#endif /* DECODER_H_ */
