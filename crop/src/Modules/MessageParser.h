/*
 * @brief MessageParser.h
 *
 */

#ifndef MESSAGEPARSER_H_
#define MESSAGEPARSER_H_

#include "ContentParser.h"
#include "DataBlockProcessing.h"
#include "../DataManagement/DataTypes.h"
#include "../Tools/Bin.h"
#include "ReceiverModuleIF.h"

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

  void registerCallback(const TextCallback& cb);
  void registerCallback(const SensorCallback& cb);

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

  DataBlockProcessing<Text_sPtr, TextParser, std::string > textProcessing;
  DataBlockProcessing<Sensor_sPtr, SensorParser, float> sensorProcessing;
};

} // namespace crodt

#endif /* MESSAGEPARSER_H_ */
