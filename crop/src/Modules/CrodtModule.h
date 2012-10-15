/*
 * @brief CrodtModule.h
 *
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "../Tools/Bin.h"
#include "../TypesConfig/Pointer.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "CrodtModuleIF.h"


#include <mutex>
#include <thread>

class Config;
struct CrodtInput;

class CrodtModule : public CrodtModuleIF
{
public:
  CrodtModule();
  virtual ~CrodtModule();

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

#endif /* CLIENTMODULE_H_ */
