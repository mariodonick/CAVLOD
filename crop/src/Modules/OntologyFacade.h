/*
 * @brief OntologyFacade.h
 *
 */

#ifndef ONTOLOGYFACADE_H_
#define ONTOLOGYFACADE_H_

#include "Ontology.h"

class OntologyFacade : public Ontology
{
public:
  OntologyFacade();
  virtual ~OntologyFacade();

private:
  const std::vector<float>& getPriortyVec() const;
  const std::vector<unsigned short int>& getWordLengthVec() const;

private:
  std::vector<float> priorities;
  std::vector<unsigned short int> wordNumbers;
};

#endif /* ONTOLOGYFACADE_H_ */
