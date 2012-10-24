/*
 * @brief SplitEncoding.h
 *
 */

#ifndef SPLITENCODING_H_
#define SPLITENCODING_H_

#include "Partitioning.h"
#include "../TypesConfig/Pointer.h"
#include "../DataManagement/CrodtIO.h"
#include "../DataManagement/Content.h"

#include <list>
#include <queue>

namespace crodt
{

struct RelevanceDataXCmp
{
  bool operator() (RelevanceData lhs, RelevanceData rhs)
  {
    return (lhs.pos.x < rhs.pos.x);
  }
};

struct RelevanceDataYCmp
{
  bool operator() (RelevanceData lhs, RelevanceData rhs)
  {
    return (lhs.pos.y<rhs.pos.y);
  }
};

class SplitEncoding : public Partitioning
{
public:
  struct GlobalPosition
  {
    uint16_t begin;
    uint16_t length;
    float relevance;

    friend std::ostream& operator<<(std::ostream& out, const GlobalPosition& frag);
  };

public:
  SplitEncoding(const Crodm_uPtr& crodm, DBQueue_uPtr& queue);
  virtual ~SplitEncoding();

private:
  void partText(const DBDataObjectID& doid, const std::string& content, const bool& usingTimestamp);
  void partSensor(const DBDataObjectID& doid, const float& value);

  const SplitEncoding::GlobalPosition transform2global(
      const RelevanceData& lp,
      const std::vector<std::size_t>& len);
  const RelevanceData transform2localRelData(
      const SplitEncoding::GlobalPosition& gp,
      const std::vector<std::size_t>& len);
  const SplitEncoding::GlobalPosition diffFrom2RelevanceData(
      const std::list<GlobalPosition>::iterator& pre,
      const std::list<GlobalPosition>::iterator& cur);

private:
  const Crodm_uPtr& crodm;
  DBQueue_uPtr& dbFifo;

  std::queue<Sensor> sensorBuffer;
};

} // namespace crodt

#endif /* SPLITENCODING_H_ */
