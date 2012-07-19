/*
 * @brief DataBlockProcessing.h
 *
 */

#ifndef DATABLOCKPROCESSING_H_
#define DATABLOCKPROCESSING_H_

#include "../DataManagement/DataBlock.h"
#include "../TypesConfig/ProtocolConstants.h"

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
  while(curContentPos < totalLength)
  {
    //only to use reinterpret cast inside the parser
    char tmp[totalLength];
    for(unsigned int i = 0; i < totalLength; ++i)
      tmp[i] = data[curContentPos + i];

    T obj = parseContent(tmp, totalLength);
    unsigned int len = obj->size();
    curContentPos += len;

    decode(dbh.dataObjectID.to_uint(), dbh.sequenceNumber.to_uint(), obj);
    display(sortedContent);
  }
}

#endif /* DATABLOCKPROCESSING_H_ */
