/*
 * @brief ByteArray.cpp implementation of member functions
 */

#include "ByteArray.h"
#include "../DataManagement/DataBlockHeader.h"
#include "../DataManagement/DataBlock.h"

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

void ByteArray::insert(char* data, const size_t& length)
{
  clear();
  append(data, length);
}

// todo inkonsistent zu append const char auf ein nenner bringen
void ByteArray::append(char* data, const size_t& length)
{
  for(unsigned int i = 0; i < length; ++i)
    vector.push_back( data[i] & 0xFF );
}

// todo inkonsistent zu append char auf ein nenner bringen
void ByteArray::append(const char* data, const size_t& length)
{
  for(unsigned int i = 0; i < length; ++i)
  {
    char tmp = data[i];
    vector.push_back(tmp);
  }
}

void ByteArray::insert(DataBlock<Text>& dataBlock)
{
  clear();
  append(dataBlock);
}

void ByteArray::insert(DataBlock<Sensor>& dataBlock)
{
  clear();
  append(dataBlock);
}

void ByteArray::insert(DataBlock<Picture>& dataBlock)
{
  clear();
  append(dataBlock);
}

//todo die whileschleife sinnvoll in eine funktion oder so
void ByteArray::append(DataBlock<Text>& dataBlock)
{
  appendHeader( dataBlock.getHeader() );

  while(!dataBlock.isContentEmpty())
  {
    append( *dataBlock.getContent() );
  }
}

void ByteArray::append(DataBlock<Sensor>& dataBlock)
{
  appendHeader( dataBlock.getHeader() );

  while(!dataBlock.isContentEmpty())
  {
    append( *dataBlock.getContent() );
  }
}

void ByteArray::append(DataBlock<Picture>& dataBlock)
{
  appendHeader( dataBlock.getHeader() );

  while(!dataBlock.isContentEmpty())
  {
    append( *dataBlock.getContent() );
  }
}

void ByteArray::append(Text& text)
{
  uint64_t timestamp = text.getTimestamp();
  append(timestamp, C_TIMESTAMP_BYTES);
  append(text.lineBreak, C_LINE_BYTES);
  append(text.text.c_str(), text.text.size());
}

void ByteArray::append(Sensor& sensor)
{
  //todo ByteArray::append sensor implementieren
}

void ByteArray::append(Picture& pic)
{
  //todo ByteArray::append pic implementieren
}

void ByteArray::appendHeader(const DataBlockHeader& header)
{
  append( header.getDataType() );
  append( header.getConfig() );
  append( header.getDataObjectID() );
  append( header.getSequenceNumber() );
  append( header.getLength() );
}

void ByteArray::setBitInChar( char& tmp, const bool& value, const unsigned int& pos)
{
  if(pos > 7){ std::cerr << "ERROR: pos reach out of 8bit char range!\n"; return;}

//  std::cout << "value: " << value << " pos: " << pos << "\n";
  tmp |= (value << pos);
//  std::cout << "tmp: 0x" << std::hex << int(tmp) << std::dec << "\n";
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

//  std::cout << "dataSize: " << vector.size() << std::endl;
//  std::cout << "DUMP" << std::endl;

  out << "\n";
}
