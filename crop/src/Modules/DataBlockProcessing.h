/*
 * @brief DataBlockProcessing.h
 *
 */

#ifndef DATABLOCKPROCESSING_H_
#define DATABLOCKPROCESSING_H_

#include "../DataManagement/DataBlock.h"
#include "../TypesConfig/Constants.h"

#include <iostream>

template<class T, class ContentParser, class Decoder, class Visualizer>
class DataBlockProcessing : protected ContentParser, protected Decoder, protected Visualizer
{
  using Decoder::decode;
  using ContentParser::parseContent;
  using Visualizer::display;
  using Decoder::sortedContent;

public:
  DataBlockProcessing();
  virtual ~DataBlockProcessing();

  void start(const DataBlock::Header& dbh, const char* data);

private:
  unsigned int curContentPos;
};



template<class T, class Parser, class Decoder, class Visualizer>
DataBlockProcessing<T, Parser, Decoder, Visualizer>::DataBlockProcessing()
: curContentPos(0)
{

}

template<class T, class Parser, class Decoder, class Visualizer>
DataBlockProcessing<T, Parser, Decoder, Visualizer>::~DataBlockProcessing()
{

}

template<class T, class Parser, class Decoder, class Visualizer>
void DataBlockProcessing<T, Parser, Decoder, Visualizer>::start(const DataBlock::Header& dbh, const char* data)
{
  std::cout << "\n---------------DBProcessing---------------------------\n";

  curContentPos = 0;
  unsigned int totalLength = dbh.length.to_uint() - DB_HEADER_LENGTH_BYTES;

  std::cout << "dblength: " << dbh.length.to_uint() << "\n";
  std::cout << "totalLength: " << totalLength << "\n";

  // todo only to use reinterpret cast inside the parser
  char tmp[totalLength];
  for(unsigned int i = 0; i < totalLength; ++i)
  {
//    std::cout << "data[" << i << "]= 0x" << std::hex << int(data[curContentPos + i] & 0xFF) << std::dec << "\n";
    tmp[i] = data[curContentPos + i];
  }

  while(curContentPos < totalLength)
  {
    bool usingTimestamp = dbh.config[DB_CONFIG_TIMESTAMP] == true;
    unsigned int offset = (usingTimestamp) ? C_TIMESTAMP_BYTES : 0;
    CTimestamp timestamp;

    if(usingTimestamp)
    {
      timestamp = char2Bin<C_TIMESTAMP_BYTES * BIT_PER_BYTE>(&tmp[curContentPos]);
      std::cout << "timestamp: " << timestamp.to_ulong() << " = 0x" << std::hex << timestamp.to_ulong() << std::dec << "\n";
    }

    curContentPos += offset;

//    std::cout << "offset: " << offset << "\n";
//    std::cout << "curContentPos: " << curContentPos << "\n";

    T obj = parseContent(&tmp[curContentPos], totalLength - offset);
    curContentPos += obj->size();

    decode(dbh.dataObjectID.to_uint(), dbh.sequenceNumber.to_uint(), obj);
    display(sortedContent, usingTimestamp, timestamp);
  }
}

#endif /* DATABLOCKPROCESSING_H_ */
