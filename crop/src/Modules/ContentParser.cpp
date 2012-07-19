/*
 * @brief ContentParser.cpp implementation of member functions
 */

#include "ContentParser.h"
#include "../TypesConfig/ProtocolConstants.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Bin.h"

#include <iostream>

TextParser::TextParser()
{

}

TextParser::~TextParser()
{

}

Text_sPtr TextParser::parseContent(char* data, const unsigned int& len)
{
  std::cout << "\n---------------Text---------------------------\n";

  CTimestamp timestamp = char2Bin<C_TIMESTAMP_BYTES * BIT_PER_BYTE>(data);
  unsigned int offset = C_TIMESTAMP_BYTES;

  uint16_t* line = reinterpret_cast<uint16_t*>( &data[offset] );
  offset += C_LINE_BYTES;

  uint16_t* column = reinterpret_cast<uint16_t*>( &data[offset] );
  offset += C_COLUMN_BYTES;

  unsigned int length = len - offset;

  Text_sPtr text( new Text );
  text->column = *column;
  text->line = *line;
  text->text.insert(0, &data[offset], length);
  text->setTimestamp( timestamp.to_ulong() );

  std::cout << "timestamp: " << timestamp.to_ulong() << "\n";
  std::cout << "line: " << text->line << "\n";
  std::cout << "column: " << text->column << "\n";
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
  float* v = reinterpret_cast<float*>( &data[C_TIMESTAMP_BYTES] );

  std::cout << "timestamp: " << timestamp.to_ulong() << " = 0x" << std::hex << timestamp.to_ulong() << std::dec << "\n";
  std::cout << "value: " << *v << "\n";

  Sensor_sPtr sensor( new Sensor );
  sensor->value = *v;
  sensor->setTimestamp( timestamp.to_ulong() );

  return sensor;
}
