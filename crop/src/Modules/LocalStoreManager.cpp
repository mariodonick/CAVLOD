/*
 * LocalStoreManager.cpp
 *
 *  Created on: 10.10.2012
 *      Author: gigi
 */

#include "LocalStoreManager.h"
#include "../Tools/ByteArray.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../TypesConfig/Config.h"
#include "../Tools/FileSystem.h"
#include "../DataManagement/DataBlock.h"

#include <string>
#include <sstream>
#include <stdio.h>
#include <dirent.h>

using namespace crodt;

LocalStoreManager::LocalStoreManager(){}

LocalStoreManager::~LocalStoreManager(){}

const std::vector<DataBlock_sPtr>& LocalStoreManager::load()
{
  dbVec.clear();

  Config* config = Config::instance();
  std::string doidFolder = config->backupPath;

  struct dirent *entry;
  DIR *doidPath_dir;
  DIR *sequenzNumber_dir;

  doidPath_dir = opendir((const char*) &doidFolder);
  //todo das mit dem entry = dirbasepath ist sehr unschön.. desewegen auch die compilermeldung
  // lös das bitte anders... bin gerade nicht sicher was er da genau macht
  while(entry = readdir(doidPath_dir))
  {
    sequenzNumber_dir = opendir(entry->d_name);
    while(entry = readdir(sequenzNumber_dir))
    {
      DataBlock_sPtr db(new DataBlock);
      DataBlock::Header dbh;
      std::string filename = entry->d_name;
      std::ifstream bin(filename.c_str(),std::ios::binary);

      bin.seekg(0,std::ios::end);  //an letzte position der datei springen
      int file_size = bin.tellg(); // position auslesen => groesse der datei
      bin.seekg(0,std::ios::beg); // wieder an anfang der datei springen

      char dataBlockEntries[file_size];
      bin.read(reinterpret_cast <char*> (&dataBlockEntries), file_size); // auslesen der daten in ausgabe array

      dbh.dataType = char2uint( &dataBlockEntries[0], 4 );
      dbh.config = char2uint( &dataBlockEntries[4], 4 );
      dbh.dataObjectID = char2uint( &dataBlockEntries[8], 4 );
      dbh.sequenceNumber = char2uint( &dataBlockEntries[12], 4 );
      dbh.length = char2uint( &dataBlockEntries[16], 4 );

      db->setHeader(dbh);

      Bin<32> time1 = char2uint( &dataBlockEntries[20], 4 );
      Bin<32> time2 = char2uint( &dataBlockEntries[24], 4 );
      db->setTimetamp(merge(time1, time2));

      ByteArray_sPtr ba(new ByteArray);
      ba->insert(&dataBlockEntries[28], file_size-28);
      db->addContent( ba );

      dbVec.push_back(db);
    }
    closedir(sequenzNumber_dir);
  }
  closedir(doidPath_dir);

  return dbVec;
}

void LocalStoreManager::store(DataBlock_sPtr& db)
{
  Config* config = Config::instance();
  ByteArray_sPtr dbContent = db->getContent();

  uint dataType_uint = db->getDataType().to_uint();
  uint config_uint = db->getConfig().to_uint();
  uint dataObjectID_uint = db->getDataObjectID().to_uint();
  uint sequenzNumber_uint = db->getSequenceNumber().to_uint();
  uint length_uint = db->getLength().to_uint();
  uint64_t timeStamp_uint = db->getTimestamp().to_ulong();

  std::stringstream ssDataType;
  ssDataType << dataType_uint;

  std::stringstream ssDOID;
  ssDOID << dataObjectID_uint;

  std::stringstream ssSequenzNumber;
  ssSequenzNumber << sequenzNumber_uint;

  std::string path = config->backupPath + ssDataType.str() + "_" + ssDOID.str() + "/" + ssSequenzNumber.str() + ".bin";
  createFolder(path);

  std::ofstream outbin(path,std::ios::binary);
  outbin.write( reinterpret_cast <const char*> (&dataType_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&config_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&dataObjectID_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&sequenzNumber_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&length_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&timeStamp_uint), sizeof(uint64_t) );
  outbin.write( dbContent->dataPtr(), dbContent->size() );
  outbin.close();
}
