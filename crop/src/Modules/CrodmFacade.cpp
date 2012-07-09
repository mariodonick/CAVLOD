/*
 * @brief CrodmFacade.cpp implementation of member functions
 */

#include "CrodmFacade.h"

CrodmFacade::CrodmFacade()
{
  priorities =  {10, 100, 80, 90,  5, 40, 23, 74, 32, 98,
                 62,   8, 30, 19,  7,  1, 99, 50, 58, 36,
                 27,  22, 88, 77, 33, 83, 92, 49, 76, 75};
  wordNumbers = { 3,   1,  3,  2, 3,  4,  2,  6,  1,  2,
                  9,   1,  1,  5, 8,  9,  3,  2,  4,  7,
                  4,  12,  1,  3, 1, 23,  1,  8,  4,  5 }; // = 150 wörter  // 30 datenblöcke
}

CrodmFacade::~CrodmFacade()
{
}

const std::vector<float>& CrodmFacade::getPriortyVec() const
{

  //todo prioritäten noch setzen!!
  return priorities;
}

const std::vector<unsigned short int>& CrodmFacade::getWordLengthVec() const
{
  return wordNumbers;
}


