/*
 * @brief ByteArray.h
 *
 */

#ifndef BYTEARRAY_H_
#define BYTEARRAY_H_

#include "Bin.h"
#include "../DataManagement/Content.h"

#include <vector>
#include <iosfwd>
#include <iostream>
#include <iomanip>

class DataBlockHeader;

class ByteArray
{
public:
  ByteArray();
  virtual ~ByteArray();

  template<unsigned int BAND_WIDTH>
  void insert(const Bin<BAND_WIDTH>& data);
  void insert(char* data, const size_t& length);

  void insert(Picture& pic);
  void insert(Text& text);
  void insert(Sensor& sensor);
  void append(Picture& pic);
  void append(Text& text);
  void append(Sensor& sensor);

  template<unsigned int BAND_WIDTH>
  void append(const Bin<BAND_WIDTH>& data);
  void append(char* data, const size_t& length);

  const char& operator[](const std::size_t& index) const;
  const Byte getByte(const std::size_t& index) const;
  const std::size_t size() const;
  char* dataPtr();
  const char* dataPtr() const;
  void clear();

  void dumpHex(std::ostream& out) const;
  void dumpBin(std::ostream& out) const;

private:
//  void appendHeader(const DataBlockHeader& header);
  template<typename T>
  void append(T& data, const std::size_t& byteLength);
  void append(const char* data, const size_t& length);

  void setBitInChar( char& tmp, const bool& value, const unsigned int& pos);

private:
  std::vector<char> vector;

  unsigned short int bitCount;
  unsigned short int curBytePos;
};

template<unsigned int BAND_WIDTH>
void ByteArray::insert(const Bin<BAND_WIDTH>& data)
{
  clear();
  append(data);
}

template<typename T>
void ByteArray::append(T& data, const std::size_t& byteLength)
{
  char* tmp = reinterpret_cast<char*>(&data);
  append(tmp, byteLength);
}

template<unsigned int BAND_WIDTH>
void ByteArray::append(const Bin<BAND_WIDTH>& data)
{
  char tmp = 0;
  bool loaded = false;

  if( bitCount != 0)
  {
    tmp = vector[curBytePos];
//    std::cout << "fertisch: curBytePos: " << curBytePos << "\n";
//    std::cout << "get old tmp: " << std::hex << int(tmp) << std::dec << "\n";
//    std::cout << "get old vector1: " << std::hex << int(vector[curBytePos]) << std::dec << "\n";
    loaded = true;
  }

  for(unsigned int i = 0; i < BAND_WIDTH; ++i)
  {
    setBitInChar(tmp, data[i], bitCount);
    ++bitCount;

    if(bitCount > 7)
    {
      if(loaded)
      {
//        std::cout << "loaded\n";
        vector[curBytePos] = tmp;
        loaded = false;
      }
      else
      {
//        std::cout << "NOT loaded\n";
        vector.push_back(tmp);
      }
      ++curBytePos;
      bitCount = 0;
      tmp = 0;
    }
  }

//  std::cout << "fertisch: bitcount: " << bitCount << "\n";

  if(bitCount > 0)
  {
//    std::cout << "last push\n";
    if(loaded)
    {
//      std::cout << "loaded\n";
      vector[curBytePos] = tmp;
    }
    else
    {
//      std::cout << "NOT loaded\n";
      vector.push_back(tmp);
    }
  }
}

#endif /* BYTEARRAY_H_ */
