/*
 * @brief SplitEncoding.h
 *
 */

#ifndef SPLITENCODING_H_
#define SPLITENCODING_H_

#include "Partitioning.h"
#include "../TypesConfig/Pointer.h"
#include "../DataManagement/RelevanceData.h"

#include <cstdint>
#include <vector>
#include <list>

class SplitEncoding : public Partitioning
{
public:
  struct GlobalPosition
  {
    uint16_t pos;
    uint16_t length;
    float relevance;

    friend std::ostream& operator<<(std::ostream& out, const GlobalPosition& frag);
  };

public:
  SplitEncoding(const Crodm_uPtr& crodm, DBQueue_uPtr& queue);
  virtual ~SplitEncoding();

private:
  void partText(const DBDataObjectID& doid, const std::string& content);
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
};

#endif /* SPLITENCODING_H_ */
