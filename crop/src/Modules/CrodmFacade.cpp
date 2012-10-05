/*
 * @brief CrodmFacade.cpp implementation of member functions
 */

#include "CrodmFacade.h"

#include <string>

CrodmFacade::CrodmFacade()
: index(0)
{
  priorities =  {0, 100, 85, 0, 64, 0, 39, 0, 71, 0};

  // no need for len_y in this case (text, sensor)
  //rel posx posy lenx leny
  relevanceData.push_back(RelevanceData({100.f, 13, 0, 14})); // = Beispieltext:\n
  relevanceData.push_back(RelevanceData({ 80.f,  0, 1,  9})); // = Hallo ich
  relevanceData.push_back(RelevanceData({ 60.f, 35, 1, 22})); // = komme vom Mars.\nDabei
  relevanceData.push_back(RelevanceData({ 30.f, 37, 2, 18})); // = dann priorisiert,
  relevanceData.push_back(RelevanceData({ 70.f, 73, 2,  4})); // = Erde
}

CrodmFacade::~CrodmFacade()
{
}

const float& CrodmFacade::getPriority(const RelevanceData& relevance, const DBDataObjectID&)
{
  if(index >= priorities.size())
    index = 0;

  // do some freaky stuff to compute the priority

  return priorities[index++];
}

const std::vector<RelevanceData>& CrodmFacade::getRelevanceData()
{
  return relevanceData;
}

void CrodmFacade::evaluateText(const std::string&)
{

}

void CrodmFacade::evaluateSensor(const float&)
{

}
