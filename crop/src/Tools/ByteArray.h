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
#include <cstring>

class DataBlockHeader;

class ByteArray
{
public:
  ByteArray();
  virtual ~ByteArray();

  template<unsigned int BAND_WIDTH>
  void insert(const Bin<BAND_WIDTH>& data);
  void insert(char* data, const size_t& length);

  void insert(crodt::Text& text);
  void insert(crodt::Sensor& sensor);
  void append(crodt::Text& text);
  void append(crodt::Sensor& sensor);

  template<unsigned int BAND_WIDTH>
  void append(const Bin<BAND_WIDTH>& data);
  void append(char* data, const size_t& length);

  const char& operator[](const std::size_t& index) const;
  const Byte getByte(const std::size_t& index) const;
  const std::size_t size() const;
  char* dataPtr();
  const char* dataPtr() const;
  void clear();
  const bool isEmpty() const;

  void dumpHex(std::ostream& out) const;
  void dumpBin(std::ostream& out) const;

private:
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
  char tmp[byteLength];
  memcpy(&tmp, &data, byteLength);

  append(tmp, byteLength);
}

template<unsigned int BAND_WIDTH>
void ByteArray::append(const Bin<BAND_WIDTH>& data)
{
  char tmp = 0;
  bool loaded = false;

  // current byte is not empty
  if( bitCount != 0)
  {
    // load the last byte
    tmp = vector[curBytePos];
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
        vector[curBytePos] = tmp;
        loaded = false;
      }
      else
      {
        vector.push_back(tmp);
      }
      ++curBytePos;
      bitCount = 0;
      tmp = 0;
    }
  }

  if(bitCount > 0)
  {
    if(loaded)
      vector[curBytePos] = tmp;
    else
      vector.push_back(tmp);
  }
}

#endif /* BYTEARRAY_H_ */
