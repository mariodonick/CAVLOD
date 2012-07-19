/*
 * @brief RelevanceData.h
 *
 */

#ifndef RELEVANCEDATA_H_
#define RELEVANCEDATA_H_

#include <cstdint>
#include <iostream>

struct RelevanceData
{
  float relevanceValue;
  uint16_t pos_x;
  uint16_t pos_y;
  uint16_t len_x;

  friend std::ostream& operator<<(std::ostream& out, const RelevanceData& rel)
  {
    out << "relevance: " << rel.relevanceValue
        << " pos_x: " << rel.pos_x
        << " pos_y: " << rel.pos_y
        << " len_x: " << rel.len_x;
    return out;
  }
};

#endif /* RELEVANCEDATA_H_ */
