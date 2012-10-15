/*
 * @brief Prioritization.h
 *
 */

#ifndef PRIORITIZATION_H_
#define PRIORITIZATION_H_

namespace crodt
{

class Prioritization
{
public:
  virtual ~Prioritization(){}

  virtual void evaluate() = 0;
};

} // namespace crodt

#endif /* PRIORITIZATION_H_ */
