/*
 * @brief CrodtIO.h
 *
 */

#ifndef CRODTIO_H_
#define CRODTIO_H_

#include <iostream>
#include <vector>

namespace crodt
{

typedef unsigned long long int uint64;
typedef unsigned short uint16;

struct Position
{
  uint16 x; // column
  uint16 y; // the line
  uint16 len_x; // lenght of the content starts by position x/y (by text the values are char precise)
};

struct RelevanceData
{
  float relevanceValue; // the relevance value
  Position pos; // the position of the relevant area

  friend std::ostream& operator<<(std::ostream& out, const RelevanceData& rel)
  {
    out << "relevance: " << rel.relevanceValue
        << " pos_x: " << rel.pos.x
        << " pos_y: " << rel.pos.y
        << " len_x: " << rel.pos.len_x;
    return out;
  }
};



struct CrodtInput
{
  // stores all information about the position of the relevant areas
  std::vector<RelevanceData> relevanceVector;
  std::string content; // cointains the content
  bool is_timestamp; // is true if we want to send a timestamp
};

template<class T>
struct COItem
{
  Position pos; // position of this item
  T content; // contains the content
  bool usingTimestamp; // is true if we want to send a timestamp
  uint64 timestamp; // contains the timestamp
};

template<class T>
struct CrodtOutput
{
  COItem<T> sortedContent; // contains the data which was produced by the crodt module
};

} // namespace crodt

#endif /* CRODTIO_H_ */
