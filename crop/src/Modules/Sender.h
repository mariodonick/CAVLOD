/*
 * @brief Sender.h
 *
 */

#ifndef SENDER_H_
#define SENDER_H_

#include "../Tools/Bin.h"
#include "../TypesConfig/Pointer.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "SenderModuleIF.h"

#include <mutex>
#include <thread>

namespace crodt
{

class Config;
struct CrodtInput;

class Sender : public SenderModuleIF
{
public:
  Sender();
  virtual ~Sender();

private:
  void initialize();

  void sendSensor(const float& value, const bool& usingTimestamp);
  void sendText(const std::string& text, const bool& usingTimestamp);
  void sendText(const CrodtInput& ci);

  void packetizerThread();

private:
  bool running;
  Config& config;

  DBQueue_uPtr dbFifo;
  DBQueue_uPtr prioQueue;

  StoreManager_uPtr dbStorage;
  Crodm_uPtr crodm;
  NetworkIO_uPtr network;
  Partitioning_uPtr partitioning;
  Prioritization_uPtr prioritization;
  Packetizer_uPtr packetizer;

  std::mutex eventMutex;
  std::thread packerThread;

  DBDataObjectID sensorId;
  DBDataObjectID textId;
};

} // namespace crodt

#endif /* SENDER_H_ */
