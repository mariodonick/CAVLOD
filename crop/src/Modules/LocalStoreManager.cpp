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
#include "../Tools/Log.h"
#include "../DataManagement/DataBlock.h"
#include "../Tools/Bin.h"

#include <string>
#include <sstream>
#include <stdio.h>
#include <dirent.h>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include <sys/stat.h>
#include <sys/types.h>

using namespace crodt;

LocalStoreManager::LocalStoreManager()
: config( *Config::instance() )
{

}

LocalStoreManager::~LocalStoreManager(){}

const std::vector<DataBlock_sPtr>& LocalStoreManager::load()
{
  dbVec.clear();

  struct block
  {
    uint type;
    uint cfg;
    uint doid;
    uint seqNum;
    uint len;
    uint64_t ts;
    uint prio;
  };

  boost::filesystem::path backup_path( config.backupPath );
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
        std::string temp = config.backupPath + dir_itr->path().filename().c_str();
        boost::filesystem::path file_path( temp );
        boost::filesystem::directory_iterator subDir_itr_end;

//        std::cout << "subDirectory: " << file_path << "\n";

        for( boost::filesystem::directory_iterator subDir_itr_begin( file_path ); subDir_itr_begin != subDir_itr_end; ++subDir_itr_begin)
        {
          try
          {
            std::cout << "path: " << temp << std::endl;
            std::cout << "filename: " << subDir_itr_begin->path().filename() << std::endl;
            DataBlock_sPtr db(new DataBlock);
            DataBlock::Header dbh;
            std::ifstream bin(temp,std::ios::binary);

            if(!bin.is_open())
            {
              std::cout << "cant open: " << temp << std::endl;
              continue;
            }

            bin.seekg(0,std::ios::end);  //an letzte position der datei springen
            uint file_size = bin.tellg(); // position auslesen => groesse der datei
            bin.seekg(0,std::ios::beg); // wieder an anfang der datei springen

            block moep;
            bin.read(reinterpret_cast <char*> (&moep), sizeof(block)); // auslesen der daten in ausgabe array

            char DBcontent[file_size-sizeof(block)];
            bin.read(DBcontent, (file_size-sizeof(block)));
            //std::cout << "dataBlockEntries: " << test << std::endl;
            std::cout << "file_size: " << sizeof(block) << std::endl;

            dbh.dataType = moep.type;
            dbh.config = moep.cfg;
            dbh.dataObjectID = moep.doid;
            dbh.sequenceNumber = moep.seqNum;
            dbh.length = moep.len;

/*            dbh.dataType = char2uint( &dataBlockEntries[0], 4 );
            dbh.config = char2uint( &dataBlockEntries[4], 4 );
            dbh.dataObjectID = char2uint( &dataBlockEntries[8], 4 );
            dbh.sequenceNumber = char2uint( &dataBlockEntries[12], 4 );
            dbh.length = char2uint( &dataBlockEntries[16], 4 );*/

            db->setHeader(dbh);

/*            Bin<32> time1 = char2uint( &dataBlockEntries[20], 4 );
            Bin<32> time2 = char2uint( &dataBlockEntries[24], 4 );
            db->setTimetamp(merge(time1, time2));

            db->setPriority( char2uint( &dataBlockEntries[28], 4) );*/

            db->setTimetamp(moep.ts);
            db->setPriority(moep.prio);

            ByteArray_sPtr ba(new ByteArray);
            ba->insert(&DBcontent[0], file_size-sizeof(block));
//
            db->addContent( ba );

            std::cout << "type: " << dbh.dataType.to_string() << " " << dbh.dataType.to_uint() << std::endl;
            std::cout << "config: " << dbh.config.to_string() << " " << dbh.config.to_uint() << std::endl;
            std::cout << "DOID: " << dbh.dataObjectID.to_string() << " " << dbh.dataObjectID.to_uint() << std::endl;
            std::cout << "SN: " << dbh.sequenceNumber.to_string() << " " << dbh.sequenceNumber.to_uint() << std::endl;
            std::cout << "length: " << dbh.length.to_string() << " " << dbh.length.to_uint() << "\n" << std::endl;
            std::cout << "prio: " << moep.prio << "\n" << std::endl;
            //std::cout << "time1: " << time1.to_string() << " " << time1.to_uint() << std::endl;
            //std::cout << "time2: " << time2.to_string() << " " << time2.to_uint() << std::endl;

            //ba->dumpHex(std::cout);

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

void LocalStoreManager::store(const DataBlock_sPtr& db)
{
  struct block
  {
    uint type;
    uint cfg;
    uint doid;
    uint seqNum;
    uint len;
    uint64_t ts;
    uint prio;
  };

  ByteArray_sPtr dbContent = db->getContent();
  block data;

  data.type = db->getDataType().to_uint();
  data.cfg = db->getConfig().to_uint();
  data.doid = db->getDataObjectID().to_uint();
  data.seqNum = db->getSequenceNumber().to_uint();
  data.len = db->getLength().to_uint();
  data.ts = db->getTimestamp().to_ulong();
  data.prio = db->getPriority();

  std::cout << "dataType: " << data.type << std::endl;
  std::cout << "config: " << data.cfg << std::endl;
  std::cout << "DOID: " << data.doid << std::endl;
  std::cout << "SN: " << data.seqNum << std::endl;
  std::cout << "legnth: " << data.len << std::endl;
  std::cout << "ts: " << data.ts << std::endl;
  std::cout << "priority: " << data.prio << std::endl;


  std::stringstream ssDataType;
  ssDataType << data.type;

  std::stringstream ssDOID;
  ssDOID << data.doid;

  std::stringstream ssSequenzNumber;
  ssSequenzNumber << data.seqNum;

  std::string path = config.backupPath + ssDataType.str() + "_" + ssDOID.str() + "/";
  createFolder(path);

  std::string filePath = path + ssSequenzNumber.str() + ".bin";
  std::ofstream outbin(filePath,std::ios::binary);

/*  outbin.write( reinterpret_cast <const char*> (&dataType_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&config_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&dataObjectID_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&sequenzNumber_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&length_uint), sizeof(uint) );
  outbin.write( reinterpret_cast <const char*> (&timeStamp_uint), sizeof(uint64_t) );
  outbin.write( reinterpret_cast <const char*> (&priority_uint), sizeof(uint) );*/

  outbin.write( reinterpret_cast <const char*> (&data), sizeof(block));
  outbin.write( dbContent->dataPtr(), dbContent->size() );

  outbin.close();
}

void LocalStoreManager::remove(const DataBlock::Header& dbh)
{
  std::stringstream dt;
  dt << dbh.dataType.to_uint();
  std::stringstream doid;
  doid << dbh.dataObjectID.to_uint();
  std::stringstream sq;
  sq<< dbh.sequenceNumber.to_uint();

  std::string folder = config.backupPath + dt.str() + "_" + doid.str() + "/";
  if( existFolder(folder) )
  {
    std::string file = folder + sq.str() + ".bin";

    if( ::remove(file.c_str()) != 0 )
    {
      perror( "Error deleting file: " );
      ERROR() << "error removing successfully" << ENDL;
    }
    else
    {
      boost::filesystem::path f = folder;
      if(boost::filesystem::is_empty(f))
        removeFolder(folder);
    }
  }
}
