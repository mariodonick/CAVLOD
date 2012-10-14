/*
 * @brief MessageParser.h
 *
 */

#ifndef MESSAGEPARSER_H_
#define MESSAGEPARSER_H_

#include "Parser.h"
#include "ContentParser.h"
#include "UniversalDecoder.h"
#include "DataBlockProcessing.h"
#include "Visualizer.h"
#include "../Tools/Bin.h"

class ByteArray;
class Config;

class MessageParser : public Parser
{
public:
  MessageParser();
  virtual ~MessageParser();

private:
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

  DataBlockProcessing<Text_sPtr, TextParser, UniversalDecoder<Text_sPtr>, TextVisualizer > textProcessing;
  DataBlockProcessing<Sensor_sPtr, SensorParser, UniversalDecoder<Sensor_sPtr>, SensorVisualizer> sensorProcessing;
};

#endif /* MESSAGEPARSER_H_ */
