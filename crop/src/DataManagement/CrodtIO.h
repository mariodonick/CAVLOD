/*
 * @brief RelevanceData.h
 *
 */

#ifndef CRODTIO_H_
#define CRODTIO_H_

#include <cstdint>
#include <iostream>
#include <vector>

struct Position
{
  uint16_t x;
  uint16_t y;
  uint16_t len_x;
};

struct RelevanceData
{
  float relevanceValue;
  Position pos;

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
  std::vector<RelevanceData> relevanceVector;
  std::string content;
  bool is_timestamp;
};

template<class T>
struct COItem
{
  Position pos;
  T content;
  bool usingTimestamp;
  uint64_t timestamp;
};

template<class T>
struct CrodtOutput
{
  std::vector<COItem<T> > sortedContent;
};

#endif /* CRODTIO_H_ */
