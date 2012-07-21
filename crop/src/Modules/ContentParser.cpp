/*
 * @brief ContentParser.cpp implementation of member functions
 */

#include "ContentParser.h"
#include "../TypesConfig/ProtocolConstants.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Bin.h"

#include <iostream>
#include <cstring>

TextParser::TextParser()
{

}

TextParser::~TextParser()
{

}

Text_sPtr TextParser::parseContent(char* data, const unsigned int& len)
{
  std::cout << "\n---------------Text---------------------------\n";

//  for(unsigned int i = 0; i < len; ++i)
//    std::cout << "data[" << i << "]= 0x" << std::hex << int(data[i] & 0xFF) << std::dec << "\n";

  CTimestamp timestamp = char2Bin<C_TIMESTAMP_BYTES * BIT_PER_BYTE>(data);
  unsigned int offset = C_TIMESTAMP_BYTES;

  CLine line = char2Bin<C_LINE_BYTES * BIT_PER_BYTE>( &data[offset] );
  offset += C_LINE_BYTES;

  CColumn column = char2Bin<C_COLUMN_BYTES * BIT_PER_BYTE>( &data[offset] );
  offset += C_COLUMN_BYTES;

  unsigned int textLength = len - offset;

  Text_sPtr text( new Text );
  text->column = column.to_uint();
  text->line = line.to_uint();
  text->text.insert(0, &data[offset], textLength);
  text->setTimestamp( timestamp );

  std::cout << "timestamp: " << timestamp.to_ulong() << " = 0x" << std::hex << timestamp.to_ulong() << std::dec << "\n";
  std::cout << "line: " << text->line.to_uint() << "\n";
  std::cout << "column: " << text->column.to_uint() << "\n";
  std::cout << "text: " << text->text << "\n";

  return text;
}





SensorParser::SensorParser()
{

}

SensorParser::~SensorParser()
{
}

Sensor_sPtr SensorParser::parseContent(char* data, const unsigned int& len)
{
  std::cout << "\n---------------Sensor---------------------------\n";

  CTimestamp timestamp = char2Bin<C_TIMESTAMP_BYTES * BIT_PER_BYTE>(data);
  float v = 0;
  memcpy(&v, &data[C_TIMESTAMP_BYTES], C_VALUE_BYTES);

  std::cout << "timestamp: " << timestamp.to_ulong() << " = 0x" << std::hex << timestamp.to_ulong() << std::dec << "\n";
  std::cout << "value: " << v << "\n";

  Sensor_sPtr sensor( new Sensor );
  sensor->value = v;
  sensor->setTimestamp( timestamp );

  return sensor;
}
