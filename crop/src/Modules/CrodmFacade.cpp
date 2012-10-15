/*
 * @brief CrodmFacade.cpp implementation of member functions
 */

#include "CrodmFacade.h"
#include "../DataManagement/DataTypes.h"

#include <string>

CrodmFacade::CrodmFacade()
: index(0)
, priority(0.f)
{
  priorities =  {0, 100, 85, 5, 64, 5, 39, 1, 71, 0};

  // no need for len_y in this case (text, sensor)
  //rel posx posy lenx leny
//  relevanceData.push_back(RelevanceData({100.f, 13, 0, 14})); // = Beispieltext:\n
//  relevanceData.push_back(RelevanceData({ 80.f,  0, 1,  9})); // = Hallo ich
//  relevanceData.push_back(RelevanceData({ 60.f, 35, 1, 22})); // = komme vom Mars.\nDabei
//  relevanceData.push_back(RelevanceData({ 30.f, 37, 2, 18})); // = dann priorisiert,
//  relevanceData.push_back(RelevanceData({ 70.f, 73, 2,  4})); // = und_
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
      priority = priorities[index++];
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

void CrodmFacade::evaluateSensor(const float& , const DBDataObjectID&)
{

}
