/*
 * @brief ContentParser.cpp implementation of member functions
 */

#include "ContentParser.h"
#include "../TypesConfig/ProtocolConstants.h"

#include <iostream>

TextParser::TextParser()
{

}

TextParser::~TextParser()
{

}

Text* TextParser::parseContent(char* data, const unsigned int& len)
{
  std::cout << "\n---------------Text---------------------------\n";

  unsigned long long int* timestamp = reinterpret_cast<unsigned long long int*>( &data );
  unsigned int offset = C_TIMESTAMP_BYTES;

  uint16_t* line = reinterpret_cast<uint16_t*>( &data[offset] );
  offset += C_LINE_BYTES;

  uint16_t* column = reinterpret_cast<uint16_t*>( &data[offset] );
  offset += C_COLUMN_BYTES;

  unsigned int length = len - offset;

  Text* text = new Text;
  text->column = *column;
  text->line = *line;
  text->text.insert(0, &data[offset], length);
  text->setTimestamp(*timestamp);

  std::cout << "timestamp: " << *timestamp << "\n";
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

Sensor* SensorParser::parseContent(char* data, const unsigned int& len)
{
  std::cout << "\n---------------Sensor---------------------------\n";

  unsigned long long int* timestamp = reinterpret_cast<unsigned long long int*>( &data );
  float* v = reinterpret_cast<float*>( &data[C_TIMESTAMP_BYTES] );

  std::cout << "timestamp: " << *timestamp << "\n";
  std::cout << "value: " << *v << "\n";

  Sensor* sensor = new Sensor;
  sensor->value = *v;
  sensor->setTimestamp(*timestamp);

  return sensor;
}
