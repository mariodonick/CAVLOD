/*
 * @brief DataBlockProcessing.h
 *
 */

#ifndef DATABLOCKPROCESSING_H_
#define DATABLOCKPROCESSING_H_

#include "../DataManagement/DataBlock.h"
#include "../DataManagement/CrodtIO.h"
#include "../TypesConfig/Constants.h"
#include "../Tools/Log.h"

#include <functional>

namespace crodt
{

template<class T, class Parser, class Decoder, class C>
class DataBlockProcessing : protected Parser, protected Decoder
{
  using Decoder::decode;
  using Decoder::sortedContent;
  using Parser::parseContent;

  typedef std::function<void(const CrodtOutput<C>)> Callback;

public:
  DataBlockProcessing();
  virtual ~DataBlockProcessing();

  void start(const DataBlock::Header& dbh, const char* data);
  void registerCallback(const Callback& cb);

private:
  unsigned int curContentPos;
  CrodtOutput<C> output;
  Callback callback;
};


template<class T, class Parser, class Decoder, class C>
DataBlockProcessing<T, Parser, Decoder, C>::DataBlockProcessing()
: curContentPos(0)
{

}

template<class T, class Parser, class Decoder, class C>
DataBlockProcessing<T, Parser, Decoder, C>::~DataBlockProcessing()
{

}

template<class T, class Parser, class Decoder, class C>
void DataBlockProcessing<T, Parser, Decoder, C>::start(const DataBlock::Header& dbh, const char* data)
{
  DBG() << "\n---------------DBProcessing---------------------------" << ENDL;

  curContentPos = 0;
  unsigned int totalLength = dbh.length.to_uint() - DB_HEADER_LENGTH_BYTES;

  DBG() << "dblength: " << dbh.length.to_uint() << ENDL;
  DBG() << "totalLength: " << totalLength << ENDL;

  while(curContentPos < totalLength)
  {
    bool usingTimestamp = dbh.config[DB_CONFIG_TIMESTAMP_INDEX] == true;
    unsigned int offset = (usingTimestamp) ? C_TIMESTAMP_BYTES : 0;
    CTimestamp timestamp = 0;

    if(usingTimestamp)
    {
      timestamp = char2Bin<C_TIMESTAMP_BYTES * BIT_PER_BYTE>(&data[curContentPos]);
      DBG() << "timestamp: " << timestamp.to_ulong() << " = 0x" << std::hex << timestamp.to_ulong() << std::dec << ENDL;
    }

    curContentPos += offset;

    T obj = parseContent(&data[curContentPos], totalLength - offset);
    curContentPos += obj->size;

    COItem<C> coi;
    coi.content = obj->content;
    coi.pos = obj->pos;
    coi.timestamp = timestamp.to_ulong();
    coi.usingTimestamp = usingTimestamp;
    coi.doid = dbh.dataObjectID.to_uint();
    coi.sequenceNumber = dbh.sequenceNumber.to_uint();

//    decode(dbh.dataObjectID.to_uint(), dbh.sequenceNumber.to_uint(), coi);

    output.sortedContent = coi;
    callback(output);
  }
  INFO() << "\n--------------- DB END ---------------------------" << ENDL;
}

template<class T, class Parser, class Decoder, class C>
void DataBlockProcessing<T, Parser, Decoder, C>::registerCallback(const Callback& cb)
{
  callback = cb;
}

} // namespace crodt

#endif /* DATABLOCKPROCESSING_H_ */
