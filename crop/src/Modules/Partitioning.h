/*
 * @brief Partitioning.h
 *
 */

#ifndef PARTITIONING_H_
#define PARTITIONING_H_

#include "../TypesConfig/ProtocolTypes.h"

#include <string>

namespace crodt
{

class Partitioning
{
public:
  virtual ~Partitioning(){}

  virtual void partText(const DBDataObjectID& doid, const std::string& content, const bool& usingTimestamp) = 0;
  virtual void partSensor(const DBDataObjectID& doid, const float& value, const bool& usingTimestamp) = 0;
};

} // namespace crodt

#endif /* PARTITIONING_H_ */
