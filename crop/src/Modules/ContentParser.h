/*
 * @brief ContentParser.h
 *
 */

#ifndef CONTENTPARSER_H_
#define CONTENTPARSER_H_

#include "../DataClasses/Content.h"

template<class T>
class ContentParser
{
protected:
  virtual ~ContentParser(){}

public:
  virtual T* parseContent(const char* data, const unsigned int& len) = 0;
};


class TextParser : public ContentParser<Text>
{
protected:
  TextParser();
  virtual ~TextParser();

protected:
  Text* parseContent(const char* data, const unsigned int& len);
};


class SensorParser : public ContentParser<Sensor>
{
protected:
  SensorParser();
  virtual ~SensorParser();

protected:
  Sensor* parseContent(const char* data, const unsigned int& len);
};


class PictureParser : public ContentParser<Picture>
{
protected:
  PictureParser();
  virtual ~PictureParser();

protected:
  Picture* parseContent(const char* data, const unsigned int& len);
};

#endif /* CONTENTPARSER_H_ */
