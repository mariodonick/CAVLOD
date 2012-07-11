/*
 * @brief CrodmFacade.cpp implementation of member functions
 */

#include "CrodmFacade.h"

#include <string>

CrodmFacade::CrodmFacade()
{
  priorities =  {0, 100, 85, 0, 64, 0, 39, 0, 71, 0};

  //rel posx posy lenx leny
  relevanceData.push_back(RelevanceData({100.f, 13, 0, 14, 0})); // = Beispieltext:\n
  relevanceData.push_back(RelevanceData({ 80.f,  0, 1,  9, 0})); // = Hallo ich
  relevanceData.push_back(RelevanceData({ 60.f, 35, 1, 22, 1})); // = komme vom Mars.\nDabei
  relevanceData.push_back(RelevanceData({ 30.f, 37, 2, 18, 0})); // = dann priorisiert,
  relevanceData.push_back(RelevanceData({ 70.f, 73, 2,  4, 0})); // = Erde
}

CrodmFacade::~CrodmFacade()
{
}

const std::vector<float>& CrodmFacade::getPriortyVec() const
{
  return priorities;
}

const std::vector<RelevanceData>& CrodmFacade::getRelevanceVec() const
{
  return relevanceData;
}

void CrodmFacade::evaluateText(const std::string&) const
{

}
