/*
 * LocalStoreManager.cpp
 *
 *  Created on: 10.10.2012
 *      Author: gigi
 */

#include "LocalStoreManager.h"
#include "../Tools/ByteArray.h"
#include "../TypesConfig/ProtocolTypes.h"

#include <string>
#include <sstream>
#include <stdio.h>
#include <dirent.h>

LocalStoreManager::LocalStoreManager(){}

LocalStoreManager::~LocalStoreManager(){}

const std::vector<DataBlock_sPtr>& LocalStoreManager::load()
{
  const char* baseFolder = "/home/gigi/Desktop/";
  const char* doidFolder = "/home/gigi/Desktop/work";
  std::string filename = "binary.bin";
  std::ifstream bin(filename.c_str(),std::ios::binary);


  struct dirent *entry;
  DIR *dirBasePath;
  DIR *dirDoidPath;

  dirBasePath = opendir(baseFolder);
  //todo das mit dem entry = dirbasepath ist sehr unschön.. desewegen auch die compilermeldung
  // lös das bitte anders... bin gerade nicht sicher was er da genau macht
  while(entry = readdir(dirBasePath))
  {
    dirDoidPath = opendir(doidFolder);
    while(entry = readdir(dirDoidPath))
    {
      //todo fill dbVec
    }
    closedir(dirDoidPath);
  }
  closedir(dirBasePath);

  return dbVec;
}

void LocalStoreManager::store(DataBlock_sPtr& db)
{
  ByteArray_sPtr dbContent = db->getContent();

  uint dataType_uint = db->getDataType().to_uint();
  uint config_uint = db->getConfig().to_uint();
  uint dataObjectID_uint = db->getDataObjectID().to_uint();
  uint sequenzNumber_uint = db->getSequenceNumber().to_uint();
  uint length_uint = db->getLength().to_uint();
  uint64_t timeStamp_uint = db->getTimestamp().to_ulong();

  std::stringstream ssDOID;
  ssDOID << dataObjectID_uint;

  std::string baseFolder = "/home/gigi/Desktop/";

  std::stringstream ssSequenzNumber;
  ssSequenzNumber << sequenzNumber_uint;

  std::string file = "binary.bin";

  std:: string finally = baseFolder + ssDOID.str() + ssSequenzNumber.str() + file;

  std::ofstream outbin(finally,std::ios::binary);
  outbin.write( reinterpret_cast <const char*> (&dataType_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&config_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&dataObjectID_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&sequenzNumber_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&length_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&timeStamp_uint), sizeof(uint64_t) );
  outbin.write( dbContent->dataPtr(), dbContent->size() );
  outbin.close();
}
