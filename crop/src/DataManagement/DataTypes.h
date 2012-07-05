/*
 * @brief DataType.h
 *
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

enum DataTypes
{
  TYPE_SENSOR = 0x0,
  TYPE_TEXT,
  TYPE_PICTURE
};

inline const std::string dataType2String(const Bin<10>& dt)
{
  switch( static_cast<DataTypes>(dt.to_uint()) )
  {
    case TYPE_SENSOR: return "TYPE_SENSOR";
    case TYPE_TEXT: return "TYPE_TEXT";
    case TYPE_PICTURE: return "TYPE_PICTURE";
  }

  return "---";
}

#endif /* DATATYPES_H_ */
