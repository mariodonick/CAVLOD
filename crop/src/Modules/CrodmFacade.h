/*
 * @brief CrodmFacade.h
 *
 */

#ifndef CRODMFACADE_H_
#define CRODMFACADE_H_

#include "Crodm.h"
#include "../DataManagement/CrodtIO.h"

namespace crodt
{

class CrodmFacade : public Crodm
{
public:
  CrodmFacade();
  virtual ~CrodmFacade();

private:
  const float& getPriority(const RelevanceData& relevance, const DBDataObjectID& doid, const DBDatatype& dt);
  const std::vector<RelevanceData>& getRelevanceData(const DBDataObjectID& doid, const DBDatatype& dt);
  void evaluateText(const std::string& text, const DBDataObjectID& doid);
  void evaluateText(const CrodtInput& ci, const DBDataObjectID& doid);
  void evaluateSensor(const float& value, const DBDataObjectID& doid);

private:
  std::vector<float> priorities;
  std::vector<RelevanceData> relevanceData;

  unsigned int index;
  float priority;
};

} // namespace crodt

#endif /* CRODMFACADE_H_ */
