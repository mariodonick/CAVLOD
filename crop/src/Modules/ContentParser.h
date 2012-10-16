/*
 * @brief ContentParser.h
 *
 */

#ifndef CONTENTPARSER_H_
#define CONTENTPARSER_H_

#include "../DataManagement/ContentProcess.h"
#include "../TypesConfig/Pointer.h"

namespace crodt
{

template<class T>
class ContentParser
{
protected:
  virtual ~ContentParser(){}

public:
  virtual T parseContent(const char* data, const unsigned int& len) = 0;
};




class TextParser : public ContentParser<Text_sPtr>
{
protected:
  TextParser();
  virtual ~TextParser();

protected:
  Text_sPtr parseContent(const char* data, const unsigned int& len);
};






class SensorParser : public ContentParser<Sensor_sPtr>
{
protected:
  SensorParser();
  virtual ~SensorParser();

protected:
  Sensor_sPtr parseContent(const char* data, const unsigned int& len);
};

} // namespace crodt

#endif /* CONTENTPARSER_H_ */
