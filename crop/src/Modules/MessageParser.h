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
  Bin<4> version;
  Bin<12> msgConfig;

  unsigned int curMsgPos;

  DataBlockProcessing<Text, TextParser, UniversalDecoder<Text>, TextVisualizer > textProcessing;
  DataBlockProcessing<Sensor, SensorParser, UniversalDecoder<Sensor>, SensorVisualizer> sensorProcessing;
  DataBlockProcessing<Picture, PictureParser, UniversalDecoder<Picture>, PictureVisualizer> pictureProcessing;
};

#endif /* MESSAGEPARSER_H_ */
