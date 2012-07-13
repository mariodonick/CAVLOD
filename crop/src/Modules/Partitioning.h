/*
 * @brief Partitioning.h
 *
 */

#ifndef PARTITIONING_H_
#define PARTITIONING_H_

#include "../TypesConfig/ProtocolTypes.h"

#include <string>

class Partitioning
{
public:
  virtual ~Partitioning(){}

  virtual void partText(const DBDataObjectID& doid, const std::string& content) = 0;
  virtual void partSensor(const DBDataObjectID& doid, const float& value) = 0;
};

#endif /* PARTITIONING_H_ */
