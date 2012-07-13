/*
 * @brief DataType.h
 *
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include "../Tools/Bin.h"

enum DataTypes
{
  TYPE_SENSOR = 0x0,
  TYPE_TEXT
};

inline const std::string dataType2String(const DBDatatype& dt)
{
  switch( static_cast<DataTypes>(dt.to_uint()) )
  {
    case TYPE_SENSOR: return "TYPE_SENSOR";
    case TYPE_TEXT: return "TYPE_TEXT";
  }

  return "---";
}

#endif /* DATATYPES_H_ */
