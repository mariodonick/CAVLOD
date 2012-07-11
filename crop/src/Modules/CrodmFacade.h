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
  const std::vector<float>& getPriortyVec() const;
  const std::vector<RelevanceData>& getRelevanceVec() const;
  void evaluateText(const std::string& text) const;

private:
  std::vector<float> priorities;
  std::vector<RelevanceData> relevanceData;
};

#endif /* CRODMFACADE_H_ */
