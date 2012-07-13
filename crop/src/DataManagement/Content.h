/*
 * @brief Content.h
 *
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#include "../Tools/Timestamp.h"

#include <string>
#include <iosfwd>

class Content
{
public:
  const uint64_t& getTimestamp() const;
  void setTimestamp(const uint64_t& time);
  void stamp();

  virtual const std::size_t size() const = 0;

protected:
  Content();
  virtual ~Content();

protected:
  Timestamp timestamp;
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
};


class Text : public Content
{
public:
  Text();
  virtual ~Text();

  const std::size_t size() const;
  friend std::ostream& operator<<(std::ostream& out, const Text& text);

public:
  uint16_t column;
  uint16_t line;

  std::string text;
};


#endif /* CONTENT_H_ */
