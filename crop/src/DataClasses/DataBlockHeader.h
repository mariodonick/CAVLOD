/*
 * @brief DataBlockHeader.h
 *
 */

#ifndef DATABLOCKHEADER_H_
#define DATABLOCKHEADER_H_

#include "../Tools/Bin.h"
#include <iosfwd>

class DataBlockHeader
{
public:
  DataBlockHeader();
  virtual ~DataBlockHeader();

  const Bin<24>& getDataObjectID() const;
  const Bin<10>& getDataType() const;
  const HalfWord& getSequenceNumber() const;
  const Bin<6>& getConfig() const;
  const HalfWord& getLength() const;

  void setDataObjectID(const Bin<24>& doid);
  void setDataType(const Bin<10>& dt);
  void setSequenceNumber(const HalfWord& sn);
  void setConfig(const Bin<6>& conf);
  void setLength(const unsigned int& len);
  void setLength(const Bin<16>& len);

  void dump(std::ostream& out);

private:
  Bin<10> dataType;
  Bin<6> config;
  Bin<24> dataObjectID;
  HalfWord sequenceNumber;
  HalfWord length;
};

#endif /* DATABLOCKHEADER_H_ */
