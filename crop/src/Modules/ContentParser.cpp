/*
 * @brief ContentParser.cpp implementation of member functions
 */

#include "ContentParser.h"
#include "../TypesConfig/Constants.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Bin.h"
#include "../Tools/Log.h"

#include <cstring>

using namespace crodt;

TextParser::TextParser()
{

}

TextParser::~TextParser()
{

}


Text_sPtr TextParser::parseContent(const char* data, const unsigned int& len)
{
  DBG() << "\n---------------Text---------------------------" << ENDL;

  CColumn column = char2Bin<C_COLUMN_BYTES * BIT_PER_BYTE>( data );
  unsigned int offset = C_LINE_BYTES;

  CLine line = char2Bin<C_LINE_BYTES * BIT_PER_BYTE>( &data[offset] );
  offset += C_COLUMN_BYTES;

  unsigned int textLength = len - offset;

  Text_sPtr text( new ContentProcess<std::string> );
  text->pos.x = column.to_uint();
  text->pos.y = line.to_uint();
  text->content.insert(0, &data[offset], textLength);
  text->pos.len_x = text->content.size();
  text->size = C_LINE_BYTES + C_COLUMN_BYTES + text->pos.len_x;

  INFO() << "line: " << text->pos.y << ENDL;
  INFO() << "column: " << text->pos.x << ENDL;
  INFO() << "text: " << text->content << ENDL;

  return text;
}





SensorParser::SensorParser()
{

}

SensorParser::~SensorParser()
{
}

Sensor_sPtr SensorParser::parseContent(const char* data, const unsigned int& len)
{
  INFO() << "\n---------------Sensor---------------------------" << ENDL;
  float v = 0;
  memcpy(&v, &data[0], C_VALUE_BYTES);

  INFO() << "Parser value: " << v << ENDL;

  Sensor_sPtr sensor( new ContentProcess<float> );

  sensor->pos.len_x = 0;
  sensor->pos.x = 0;
  sensor->pos.y = 0;
  sensor->content = v;
  sensor->size = C_VALUE_BYTES;

  return sensor;
}
