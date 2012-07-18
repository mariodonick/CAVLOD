/*
 * @brief Crodm.h - Content Relevance-oriented Data Management
 *
 */

#ifndef CRODM_H_
#define CRODM_H_

#include "../DataManagement/RelevanceData.h"

#include <vector>
#include <bits/stringfwd.h>


class Crodm
{
public:
  virtual ~Crodm(){}

  // interface from prioritizer to Crodm
  virtual const std::vector<float>& getPriortyVec() const = 0;

  //interface from split and encoder to Crodm
  virtual const std::vector<RelevanceData>& getRelevanceData() const = 0;

  //interfaces from content phase to Crodm
  virtual void evaluateText(const std::string& text) const = 0;
  virtual void evaluateSensor(const float& value) const = 0;
};

#endif /* CRODM_H_ */
