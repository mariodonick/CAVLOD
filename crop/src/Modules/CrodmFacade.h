/*
 * @brief CrodmFacade.h
 *
 */

#ifndef CRODMFACADE_H_
#define CRODMFACADE_H_

#include "Crodm.h"
#include "../DataManagement/RelevanceData.h"

class CrodmFacade : public Crodm
{
public:
  CrodmFacade();
  virtual ~CrodmFacade();

private:
  const float& getPriorty(const RelevanceData& relevance, const DataTypes& dt);
  const std::vector<RelevanceData>& getRelevanceData();
  void evaluateText(const std::string& text);
  void evaluateSensor(const float& value);

private:
  std::vector<float> priorities;
  std::vector<RelevanceData> relevanceData;

  unsigned int index;
};

#endif /* CRODMFACADE_H_ */
