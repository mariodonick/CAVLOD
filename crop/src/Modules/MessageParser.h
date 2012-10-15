/*
 * @brief MessageParser.h
 *
 */

#ifndef MESSAGEPARSER_H_
#define MESSAGEPARSER_H_

#include "ContentParser.h"
#include "UniversalDecoder.h"
#include "DataBlockProcessing.h"
#include "../DataManagement/DataTypes.h"
#include "../Tools/Bin.h"

#include <string>

class ByteArray;

namespace crodt
{

class Config;

class MessageParser
{
public:
  MessageParser();
  virtual ~MessageParser();

  template<class T>
  void registerCallback(const std::function<void(const CrodtOutput<T>&)>& cb, const DataTypes& dt);

  void parse(const ByteArray& data);

private:
  void parse_v1(const ByteArray& data);
  void parseDB(const ByteArray& data);

  const std::size_t computeFirstDBByte();

private:
  Config& config;
  MsgVersion version;
  MsgConfig msgConfig;

  unsigned int curMsgPos;

  DataBlockProcessing<Text_sPtr, TextParser, UniversalDecoder<COItem<std::string> >, std::string > textProcessing;
//  DataBlockProcessing<float, SensorParser<float, UniversalDecoder<Content_sPtr<float> > > sensorProcessing;
};

template<class T>
void MessageParser::registerCallback(const std::function<void(const CrodtOutput<T>&)>& cb, const DataTypes& dt)
{
  switch(dt)
  {
    case TYPE_SENSOR: break;
    case TYPE_TEXT: textProcessing.registerCallback(cb); break;
  }
}

} // namespace crodt

#endif /* MESSAGEPARSER_H_ */
