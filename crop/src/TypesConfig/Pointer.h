/*
 * @brief Pointer.h
 *
 */

#ifndef POINTER_H_
#define POINTER_H_

#include <memory>
#include <string>

class DataBlock;
template<class T> class Queue;
template<class T> class ContentInput;
class Crodm;
class NetworkIO;
class Partitioning;
class Prioritization;
class Packetizer;
class MessageParser;
template<class T> class ContentProcess;

class ByteArray;


typedef std::shared_ptr<DataBlock> DataBlock_sPtr;
typedef std::shared_ptr<ByteArray> ByteArray_sPtr;

typedef std::shared_ptr<ContentProcess<std::string> > Text_sPtr;
typedef std::shared_ptr<ContentProcess<float> > Sensor_sPtr;

typedef std::shared_ptr<ContentInput<float> > SensorInput_sPtr;
typedef std::shared_ptr<ContentInput<std::string> > TextInput_sPtr;

typedef std::unique_ptr<Queue<DataBlock_sPtr> > DBQueue_uPtr;
typedef std::unique_ptr<Crodm> Crodm_uPtr;

typedef std::unique_ptr<NetworkIO> NetworkIO_uPtr;
typedef std::unique_ptr<Partitioning> Partitioning_uPtr;
typedef std::unique_ptr<Prioritization> Prioritization_uPtr;
typedef std::unique_ptr<Packetizer> Packetizer_uPtr;
typedef std::unique_ptr<MessageParser> Parser_uPtr;


#endif /* POINTER_H_ */
