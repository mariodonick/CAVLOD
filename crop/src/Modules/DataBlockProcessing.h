/*
 * @brief DataBlockProcessing.h
 *
 */

#ifndef DATABLOCKPROCESSING_H_
#define DATABLOCKPROCESSING_H_

#include <iostream>

#include "../DataClasses/DataBlock.h"
#include "../DataClasses/DataBlockHeader.h"
#include "../Config.h"
#include "../Types.h"

template<class T, class Parser, class Decoder, class Visualizer>
class DataBlockProcessing : protected Parser, protected Decoder, protected Visualizer
{
  using Decoder::decode;
  using Parser::parseContent;
  using Visualizer::display;
  using Decoder::sortedContent;

public:
  DataBlockProcessing();
  virtual ~DataBlockProcessing();

  void start(const DataBlockHeader& dbh, const char* data);

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
//  std::cout << "destructor DataBlockProcessing\n";
}

template<class T, class Parser, class Decoder, class Visualizer>
void DataBlockProcessing<T, Parser, Decoder, Visualizer>::start(const DataBlockHeader& dbh, const char* data)
{
  std::cout << "\n---------------DBProcessing---------------------------\n";

  curContentPos = 0;
  unsigned int totalLength = dbh.getLength().to_uint() - DB_HEADER_LENGTH_BYTES;
//  std::cout << "totalLength: " << totalLength << "\n";
  std::cout << "dblength: " << dbh.getLength().to_uint() << "\n";
  while(curContentPos < totalLength)
  {
    T* obj = parseContent(&data[curContentPos], totalLength);
    unsigned int len = obj->size();
    curContentPos += len;
//    std::cout << "curContentPos: " << curContentPos << " Bytes\n";

    decode(dbh.getDataObjectID().to_uint(), dbh.getSequenceNumber().to_uint(), obj);

    std::cout << "display Text: \n";
    std::cout << "-------------------------------------------------------\n";
    display(sortedContent);
    std::cout << "\n\n";
  }
}

#endif /* DATABLOCKPROCESSING_H_ */
