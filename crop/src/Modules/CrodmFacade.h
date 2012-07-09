/*
 * @brief CrodmFacade.h
 *
 */

#ifndef CRODMFACADE_H_
#define CRODMFACADE_H_

#include "Crodm.h"

class CrodmFacade : public Crodm
{
public:
  CrodmFacade();
  virtual ~CrodmFacade();

private:
  const std::vector<float>& getPriortyVec() const;
  const std::vector<unsigned short int>& getWordLengthVec() const;

private:
  std::vector<float> priorities;
  std::vector<unsigned short int> wordNumbers;
};

#endif /* CRODMFACADE_H_ */
