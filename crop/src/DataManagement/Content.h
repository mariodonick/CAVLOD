/*
 * @brief Content.h
 *
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/Timestamp.h"
#include "../Tools/Bin.h"

#include <string>
#include <iosfwd>

namespace crodt
{

class Content
{
public:
  virtual const std::size_t size() const = 0;

protected:
  Content();
  virtual ~Content();
};


class Sensor : public Content
{
public:
  Sensor();
  virtual ~Sensor();

  const std::size_t size() const;
  friend std::ostream& operator<<(std::ostream& out, const Sensor& sensor);

public:
  float value;
  Timestamp time;
};


class Text : public Content
{
public:
  Text();
  virtual ~Text();

  const std::size_t size() const;
  friend std::ostream& operator<<(std::ostream& out, const Text& text);

public:
  CColumn column;
  CLine line;

  std::string text;
};

} // namespace crodt

#endif /* CONTENT_H_ */
