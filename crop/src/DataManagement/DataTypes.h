/*
 * @brief DataType.h
 *
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include "../Tools/Bin.h"

namespace crodt
{

enum DataTypes
{
  TYPE_SENSOR = 0x0,
  TYPE_TEXT = 0x1
};

inline const std::string dataType2String(const DataTypes& dt)
{
  switch( dt )
  {
    case TYPE_SENSOR: return "TYPE_SENSOR";
    case TYPE_TEXT: return "TYPE_TEXT";
  }

  return "---";
}

template<unsigned int N>
inline const std::string dataType2String(const Bin<N>& dataTypes)
{
  return dataType2String(static_cast<DataTypes>( dataTypes.to_ulong() ) );
}

} // namespace crodt

#endif /* DATATYPES_H_ */
