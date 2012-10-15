/*
 * @brief CrodmFacade.cpp implementation of member functions
 */

#include "CrodmFacade.h"
#include "../DataManagement/DataTypes.h"
#include "../Tools/Bin.h"

#include <string>

using namespace crodt;

CrodmFacade::CrodmFacade()
: index(0)
, priority(0.f)
{

}

CrodmFacade::~CrodmFacade()
{
}

const float& CrodmFacade::getPriority(const RelevanceData& relevance, const DBDataObjectID& , const DBDatatype& dt)
{
  // do some freaky stuff to compute the priority

  if(index >= priorities.size())
    index = 0;

  priority = 0.f;
  switch( static_cast<DataTypes>(dt.to_uint()) )
  {
    case TYPE_SENSOR: break;
    case TYPE_TEXT:
    {
      priority = relevance.relevanceValue;
      std::cout << "priority: " << priority << "\n";
      std::cout << "relevance crodm: " << relevance << "\n";
      break;
    }
  }

  return priority;
}

const std::vector<RelevanceData>& CrodmFacade::getRelevanceData(const DBDataObjectID& doid, const DBDatatype& dt)
{
  return relevanceData;
}

void CrodmFacade::evaluateText(const std::string& , const DBDataObjectID&)
{

}

void CrodmFacade::evaluateText(const CrodtInput& ci, const DBDataObjectID& doid)
{
  relevanceData = ci.relevanceVector;

  priorities.clear();
  for(std::vector<RelevanceData>::iterator it = relevanceData.begin(); it != relevanceData.end(); ++it)
    priorities.push_back( it->relevanceValue );
}

void CrodmFacade::evaluateSensor(const float& , const DBDataObjectID&)
{

}
