/*
 * @brief ByteArray.cpp implementation of member functions
 */

#include "ByteArray.h"
#include "../TypesConfig/Constants.h"

ByteArray::ByteArray()
: bitCount(0)
, curBytePos(0)
{
  clear();
}

ByteArray::~ByteArray()
{
}

const char& ByteArray::operator[](const std::size_t& index) const
{
  return vector[index];
}

const Byte ByteArray::getByte(const std::size_t& index) const
{
  return static_cast<Byte>(vector[index]);
}

const std::size_t ByteArray::size() const
{
  return vector.size();
}

char* ByteArray::dataPtr()
{
  return &vector[0];
}

const char* ByteArray::dataPtr() const
{
  return &vector[0];
}

void ByteArray::clear()
{
  vector.clear();
  bitCount = 0;
  curBytePos = 0;
}

const bool ByteArray::isEmpty() const
{
  return vector.empty();
}

void ByteArray::insert(char* data, const size_t& length)
{
  clear();
  append(data, length);
}

void ByteArray::append(char* data, const size_t& length)
{
  for(unsigned int i = 0; i < length; ++i)
    vector.push_back( data[i] & 0xFF );

  curBytePos += length;
  bitCount = 0;
}

void ByteArray::append(const char* data, const size_t& length)
{
  char tmp[length];
  for(unsigned int i = 0; i < length; ++i)
    tmp[i] = data[i];

  append(tmp, length);
}

void ByteArray::insert(Text& text)
{
  vector.clear();
  append(text);
}

void ByteArray::insert(Sensor& sensor)
{
  vector.clear();
  append(sensor);
}

void ByteArray::append(Text& text)
{
  append(text.column);
  append(text.line);
  append(text.text.c_str(), text.text.size());
}

void ByteArray::append(Sensor& sensor)
{
  append(sensor.value, C_VALUE_BYTES);
}

void ByteArray::setBitInChar( char& tmp, const bool& value, const unsigned int& pos)
{
  if(pos > 7){ std::cerr << "ERROR: pos reach out of 8bit char range!\n"; return;}

  tmp |= (value << pos);
}

void ByteArray::dumpHex(std::ostream& out) const
{
  out << "{ " << std::hex;
  for(std::vector<char>::const_iterator it = vector.begin(); it != vector.end(); ++it)
    out << "0x" << static_cast<Byte>(*it).to_uint() << " ";

  out << std::dec << "}\n";
}

void ByteArray::dumpBin(std::ostream& out) const
{
  out << "\n";
  for(std::vector<char>::const_iterator it = vector.begin(); it != vector.end(); ++it)
    out << Byte(*it).to_string() << "\n";

  out << "\n";
}
