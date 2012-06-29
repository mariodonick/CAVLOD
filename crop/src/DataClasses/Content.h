/*
 * @brief Content.h
 *
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#include "../Tools/Timestamp.h"
#include "../Config.h"

#include <string>
#include <iostream>

class Content
{
public:
  const uint64_t& getTimestamp() const
  {
    return timestamp.getTime();
  }

  void setTimestamp(const uint64_t& time)
  {
    timestamp.setTimestamp(time);
  }

  void stamp()
  {
    timestamp.stamp();
  }

  virtual const std::size_t size() const = 0;

protected:
  Content(){}
  virtual ~Content(){}

protected:
  Timestamp timestamp;
};


class Sensor : public Content
{
public:
  Sensor(){}
  virtual ~Sensor(){}

  const std::size_t size() const
  {
    return C_TIMESTAMP_BYTES + C_VALUE_BYTES;
  }

  friend std::ostream& operator<<(std::ostream& out, const Sensor& sensor)
  {
    out << sensor.value;
    return out;
  }

  float value;
};


class Text : public Content
{
public:
  Text(){}
  virtual ~Text(){}

  const std::size_t size() const
  {
    return C_TIMESTAMP_BYTES + C_LINE_BYTES + text.size();
  }

  friend std::ostream& operator<<(std::ostream& out, const Text& text)
  {
    return out << text.text;
  }

  uint8_t lineBreak; // byte allign -> true false
  std::string text;
};

//class Color
//{
//public:
//  float r, g, b;
//};

class Picture : public Content
{
public:
  Picture(){} // todo grösse angeben
  virtual ~Picture(){}

  const std::size_t size() const
  {
    return C_TIMESTAMP_BYTES; // todo länge noch ausrechnen
  }

  friend std::ostream& operator<<(std::ostream& out, const Picture& pic)
  {
    out << "implement me!";
    return out;
  }

//  std::vector<Color> pic; // todo wie speichern?
};


#endif /* CONTENT_H_ */
