/*
 * @brief ContentParser.cpp implementation of member functions
 */

#include "ContentParser.h"
#include "../Config.h"

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
  uint8_t* line = reinterpret_cast<uint8_t*>( &data[C_TIMESTAMP_BYTES] );

  unsigned int pos = C_TIMESTAMP_BYTES + C_LINE_BYTES;
  unsigned int length = len - pos;

  Text* text = new Text;
  text->lineBreak = *line;
  text->text.insert(0, &data[pos], length);
  text->setTimestamp(*timestamp);

  std::cout << "timestamp: " << *timestamp << "\n";
  std::cout << "line: " << std::hex << int(text->lineBreak) << std::dec << "\n";
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





PictureParser::PictureParser()
{

}

PictureParser::~PictureParser()
{
}

Picture* PictureParser::parseContent(char* data, const unsigned int& len)
{
  std::cout << "\n---------------Picture---------------------------\n";
  Picture* picture = new Picture;
  //todo implementieren
  return picture;
}

