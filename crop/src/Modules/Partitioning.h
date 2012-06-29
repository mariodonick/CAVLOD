/*
 * @brief Partitioning.h
 *
 */

#ifndef PARTITIONING_H_
#define PARTITIONING_H_

#include "../Tools/Bin.h"

#include <vector>

class Partitioning
{
public:
  virtual ~Partitioning(){}

  virtual void partText(const Bin<24>& doid, const std::string& content) = 0;
  virtual void partSensor(const Bin<24>& doid, const float& value) = 0;
};

#endif /* PARTITIONING_H_ */
