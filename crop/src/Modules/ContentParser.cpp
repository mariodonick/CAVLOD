/*
 * @brief ContentParser.cpp implementation of member functions
 */

#include "ContentParser.h"
#include "../Config.h"

#include <iostream>

//todo aufräumen code dopplungen entfernen

TextParser::TextParser()
{

}

TextParser::~TextParser()
{
//  std::cout << "destructor TextParser\n";
}

Text* TextParser::parseContent(const char* data, const unsigned int& len)
{
  std::cout << "\n---------------Text---------------------------\n";
  Text* text = new Text;

  char tmp[len];
  for(unsigned int i = 0; i < len; ++i)
  {
//    std::cout << std::hex << "data[]: 0x" << int(data[i]) << std::dec << "\n";
    tmp[i] = data[i];
  }

  unsigned long long int* timestamp = reinterpret_cast<unsigned long long int*>( &tmp );
  uint8_t* line = reinterpret_cast<uint8_t*>( &tmp[C_TIMESTAMP_BYTES] );

  unsigned int pos = C_TIMESTAMP_BYTES + C_LINE_BYTES;
  unsigned int length = len - pos;

  text->lineBreak = *line;
  text->text.insert(0, &tmp[pos], length);
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
//  std::cout << "destructor SensorParser\n";
}

Sensor* SensorParser::parseContent(const char* data, const unsigned int& len)
{
  std::cout << "\n---------------Sensor---------------------------\n";
  Sensor* sensor = new Sensor;

  char tmp[len];
  for(unsigned int i = 0; i < len; ++i)
  {
//    std::cout << std::hex << "data[]: 0x" << int(data[i]) << std::dec << "\n";
    tmp[i] = data[i];
  }

  unsigned long long int* timestamp = reinterpret_cast<unsigned long long int*>( &tmp );
  float* v = reinterpret_cast<float*>( &tmp[C_TIMESTAMP_BYTES] );

  std::cout << "timestamp: " << *timestamp << "\n";
  std::cout << "value: " << *v << "\n";

  sensor->value = *v;
  sensor->setTimestamp(*timestamp);

  return sensor;
}





PictureParser::PictureParser()
{

}

PictureParser::~PictureParser()
{
//  std::cout << "destructor PictureParser\n";
}

Picture* PictureParser::parseContent(const char* data, const unsigned int& len)
{
//  std::cout << "\n---------------Picture---------------------------\n";
  Picture* picture = new Picture;
  //todo implementieren
  return picture;
}

