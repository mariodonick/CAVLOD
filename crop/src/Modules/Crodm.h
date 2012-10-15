/*
 * @brief Crodm.h - Content Relevance-oriented Data Management
 *
 */

#ifndef CRODM_H_
#define CRODM_H_

#include "../DataManagement/CrodtIO.h"
#include "../TypesConfig/ProtocolTypes.h"

#include <vector>
#include <bits/stringfwd.h>


class Crodm
{
public:
  virtual ~Crodm(){}

  // interface from prioritizer to Crodm
  virtual const float& getPriority(const RelevanceData& relevance, const DBDataObjectID& doid, const DBDatatype& dt) = 0;

  //interface from split and encoder to Crodm
  virtual const std::vector<RelevanceData>& getRelevanceData(const DBDataObjectID& doid, const DBDatatype& dt) = 0;

  //interfaces from content phase to Crodm
  virtual void evaluateText(const std::string& text, const DBDataObjectID& doid) = 0;
  virtual void evaluateSensor(const float& value, const DBDataObjectID& doid) = 0;
};

#endif /* CRODM_H_ */
