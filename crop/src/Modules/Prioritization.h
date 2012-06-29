/*
 * @brief Prioritization.h
 *
 */

#ifndef PRIORITIZATION_H_
#define PRIORITIZATION_H_

class Prioritization
{
public:
  virtual ~Prioritization(){}

  virtual void evaluate() = 0;
};

#endif /* PRIORITIZATION_H_ */
