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
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

using namespace crodt;

LocalStoreManager::LocalStoreManager(){}

LocalStoreManager::~LocalStoreManager(){}

const std::vector<DataBlock_sPtr>& LocalStoreManager::load()
{
  dbVec.clear();

  Config* config = Config::instance();
  boost::filesystem::path backup_path( config->backupPath );
  std::string filename;

  if ( !boost::filesystem::exists( backup_path ) )
  {
    std::cout << "\nNot found: " << backup_path.c_str() << std::endl;
    return dbVec;
  }

  boost::filesystem::directory_iterator end_itr;
  for( boost::filesystem::directory_iterator dir_itr( backup_path ); dir_itr != end_itr; ++dir_itr )
  {
    std::cout << dir_itr->path().filename() << std::endl;
    try
    {
      if(boost::filesystem::is_directory( backup_path ))
      {
        std::string temp = config->backupPath + dir_itr->path().filename().c_str();
        boost::filesystem::path file_path( temp );
        boost::filesystem::directory_iterator subDir_itr_end;

        std::cout << "subDirectory: " << file_path << "\n";

        for( boost::filesystem::directory_iterator subDir_itr_begin( file_path ); subDir_itr_begin != subDir_itr_end; ++subDir_itr_begin)
        {
          try
          {
            DataBlock_sPtr db(new DataBlock);
            DataBlock::Header dbh;
            std::ifstream bin(temp,std::ios::binary);

            if(!bin.is_open())
            {
              std::cout << "cant open: " << temp << std::endl;
              continue;
            }

            bin.seekg(0,std::ios::end);  //an letzte position der datei springen
            int file_size = bin.tellg(); // position auslesen => groesse der datei
            bin.seekg(0,std::ios::beg); // wieder an anfang der datei springen

            std::cout << "filesize: " << file_size << std::endl;
            char dataBlockEntries[file_size];
            bin.read(reinterpret_cast <char*> (&dataBlockEntries), file_size); // auslesen der daten in ausgabe array
            char* test = (reinterpret_cast <char*> (&dataBlockEntries));
            std::cout << "dataBlockEntries: " << std::hex << test << std::endl;

            dbh.dataType = char2uint( &dataBlockEntries[0], 4 );
            dbh.config = char2uint( &dataBlockEntries[4], 4 );
            dbh.dataObjectID = char2uint( &dataBlockEntries[8], 4 );
            dbh.sequenceNumber = char2uint( &dataBlockEntries[12], 4 );
            dbh.length = char2uint( &dataBlockEntries[16], 4 );

            db->setHeader(dbh);

            Bin<32> time1 = char2uint( &dataBlockEntries[20], 4 );
            Bin<32> time2 = char2uint( &dataBlockEntries[24], 4 );
            db->setTimetamp(merge(time1, time2));

            db->setPriority( char2uint( &dataBlockEntries[28], 4) );

            ByteArray_sPtr ba(new ByteArray);
            ba->insert(&dataBlockEntries[32], file_size-32);
            db->addContent( ba );

            dbVec.push_back(db);
            bin.close();
          }
          catch( const std::exception & ex )
          {
            std::cout << subDir_itr_begin->path().filename() << " " << ex.what() << std::endl;
          }
        }
      }
    }
    catch( const std::exception & ex )
    {
      std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
    }
  }
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
  uint priority_uint = db->getPriority();

  std::stringstream ssDataType;
  ssDataType << dataType_uint;

  std::stringstream ssDOID;
  ssDOID << dataObjectID_uint;

  std::stringstream ssSequenzNumber;
  ssSequenzNumber << sequenzNumber_uint;

  std::string path = config->backupPath + ssDataType.str() + "_" + ssDOID.str() + "/";
  createFolder(path);

  std::string filePath = path + ssSequenzNumber.str() + ".text";
  std::ofstream outbin(filePath,std::ios::binary);
  outbin.write( reinterpret_cast <const char*> (&dataType_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&config_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&dataObjectID_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&sequenzNumber_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&length_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&timeStamp_uint), sizeof(uint64_t) );
  outbin.write( reinterpret_cast <const char*> (&priority_uint), sizeof(uint) );
  outbin.write( dbContent->dataPtr(), dbContent->size() );

  outbin.close();
}
