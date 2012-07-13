/*
 * @brief Content.cpp implementation of member functions
 */

#include "Content.h"
#include "../TypesConfig/ProtocolConstants.h"

#include <iostream>

Content::Content()
{

}

Content::~Content()
{

}

const uint64_t& Content::getTimestamp() const
{
  return timestamp.getTime();
}

void Content::setTimestamp(const uint64_t& time)
{
  timestamp.setTimestamp(time);
}

void Content::stamp()
{
  timestamp.stamp();
}




Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

const std::size_t Sensor::size() const
{
  return C_TIMESTAMP_BYTES + C_VALUE_BYTES;
}

std::ostream& operator<<(std::ostream& out, const Sensor& sensor)
{
  out << sensor.value;
  return out;
}




Text::Text()
{

}

Text::~Text()
{

}

const std::size_t Text::size() const
{
  return C_TIMESTAMP_BYTES + C_LINE_BYTES + text.size();
}

std::ostream& operator<<(std::ostream& out, const Text& text)
{
  return out << text.text;
}

