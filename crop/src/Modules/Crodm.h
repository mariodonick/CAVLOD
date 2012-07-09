/*
 * @brief Crodm.h - Content Relevance-oriented Data Management
 *
 */

#ifndef CRODM_H_
#define CRODM_H_

#include <vector>

class Crodm
{
public:
  virtual ~Crodm(){}

  // interface from prioritizer to Crodm
  virtual const std::vector<float>& getPriortyVec() const = 0;

  //interface from split and encoder to Crodm
  virtual const std::vector<unsigned short int>& getWordLengthVec() const = 0;
};

#endif /* CRODM_H_ */
