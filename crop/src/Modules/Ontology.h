/*
 * @brief Ontology.h
 *
 */

#ifndef ONTOLOGY_H_
#define ONTOLOGY_H_

#include <vector>

class Ontology
{
public:
  virtual ~Ontology(){}

  // interface from prioritizer to ontology
  virtual const std::vector<float>& getPriortyVec() const = 0;

  //interface from split and encoder to ontology
  virtual const std::vector<unsigned short int>& getWordLengthVec() const = 0;
};

#endif /* ONTOLOGY_H_ */
