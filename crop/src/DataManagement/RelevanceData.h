/*
 * @brief RelevanceData.h
 *
 */

#ifndef RELEVANCEDATA_H_
#define RELEVANCEDATA_H_

#include <cstdint>

//all values starting with zero
struct RelevanceData
{
  float relevanceValue;
  uint16_t pos_x;
  uint16_t pos_y;
  uint16_t len_x;
  uint16_t len_y;
};

#endif /* RELEVANCEDATA_H_ */
