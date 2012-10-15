/*
 * @brief Content.cpp implementation of member functions
 */

#include "Content.h"
#include "../TypesConfig/Constants.h"

#include <iostream>

using namespace crodt;

Content::Content()
{

}

Content::~Content()
{

}




Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

const std::size_t Sensor::size() const
{
  return C_VALUE_BYTES;
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
  return C_LINE_BYTES + C_COLUMN_BYTES + text.size();
}

std::ostream& operator<<(std::ostream& out, const Text& text)
{
  return out << text.text;
}

