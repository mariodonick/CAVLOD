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

#include <fstream>
#include <string>
#include <sstream>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

using namespace crodt;

struct BinFileHeader
{
  uint16_t dataType;
  uint8_t config;
  uint32_t dataObjectID;
  uint16_t sequenzNumber;
  uint16_t length;
  uint64_t timeStamp;
  float priority;
};

LocalStoreManager::LocalStoreManager()
: config( *Config::instance() )
{

}

LocalStoreManager::~LocalStoreManager(){}

const std::vector<DataBlock_sPtr>& LocalStoreManager::load()
{
  dbVec.clear();

  boost::filesystem::path backup_path( config.backupPath );
  std::string filename;

  if ( !boost::filesystem::exists( backup_path ) )
  {
    WARNING() << "\nNot found: " << backup_path.c_str() << ENDL;
    return dbVec;
  }

  boost::filesystem::directory_iterator end_itr;
  for( boost::filesystem::directory_iterator dir_itr( backup_path ); dir_itr != end_itr; ++dir_itr )
  {
    try
    {
      if(boost::filesystem::is_directory( backup_path ))
      {
        std::string temp = dir_itr->path().string();
        boost::filesystem::path file_path( temp );
        boost::filesystem::directory_iterator subDir_itr_end;

        for( boost::filesystem::directory_iterator dir_it( file_path ); dir_it != subDir_itr_end; ++dir_it)
        {
          try
          {
            boost::filesystem::path filePath = config.backupPath;
            filePath /= dir_itr->path().filename();
            filePath /= dir_it->path().filename();

            std::fstream bin(filePath.string(), std::ios::binary | std::ios::in);

            if(!bin.is_open())
            {
              ERROR() << "cannot open: " << filePath << ENDL;
              continue;
            }

            bin.seekg(0,std::ios::end);  //an letzte position der datei springen
            int file_size = bin.tellg(); // position auslesen => groesse der datei
            bin.seekg(0,std::ios::beg); // wieder an anfang der datei springen

            char buffer[file_size];
            bin.read( buffer, sizeof(BinFileHeader));
            BinFileHeader h;
            memcpy(&h, &buffer, sizeof(BinFileHeader));

            DataBlock::Header dbh;
            dbh.dataType = h.dataType;
            dbh.config = h.config;
            dbh.dataObjectID = h.dataObjectID;
            dbh.sequenceNumber = h.sequenzNumber;
            dbh.length = h.length;

            DataBlock_sPtr db(new DataBlock);
            db->setHeader(dbh);
            db->setTimestamp(h.timeStamp);
            db->setPriority( h.priority );

            char buffer2[file_size - sizeof(BinFileHeader)];
            bin.read( buffer2, file_size - sizeof(BinFileHeader));

            ByteArray_sPtr ba(new ByteArray);
            ba->insert(buffer2, file_size - sizeof(BinFileHeader));
            db->insertContent( ba );

            dbVec.push_back(db);
            bin.close();
          }
          catch( const std::exception & ex )
          {
            ERROR() << dir_it->path().filename() << " " << ex.what() << ENDL;
          }
        }
      }
    }
    catch( const std::exception & ex )
    {
      ERROR() << dir_itr->path().filename() << " " << ex.what() << ENDL;
    }
  }
  return dbVec;
}

void LocalStoreManager::store(const DataBlock_sPtr& db)
{
  BinFileHeader h;
  h.dataType = db->getDataType().to_uint();
  h.config = db->getConfig().to_uint();
  h.dataObjectID = db->getDataObjectID().to_uint();
  h.sequenzNumber = db->getSequenceNumber().to_uint();
  h.length = db->getLength().to_uint();
  h.timeStamp = db->getTimestamp().to_ulong();
  h.priority = db->getPriority();

  std::stringstream ssDataType;
  ssDataType << h.dataType;

  std::stringstream ssDOID;
  ssDOID << h.dataObjectID;

  std::stringstream ssSequenzNumber;
  ssSequenzNumber << h.sequenzNumber;

  std::string path = config.backupPath + ssDataType.str() + "_" + ssDOID.str() + "/";
  createFolder(path);

  std::string filePath = path + ssSequenzNumber.str() + ".bin";

  std::fstream outbin(filePath, std::ios::binary | std::ios::out);
  outbin.write( reinterpret_cast <char*>(&h), sizeof(BinFileHeader) );

  ByteArray_sPtr dbContent = db->getContent();
  outbin.write( dbContent->dataPtr(), dbContent->size());

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
      perror( "Deleting file failed" );
      WARNING() << "file removing not successfully: " << file << ENDL;
    }
    else
    {
      boost::filesystem::path f = folder;
      if(boost::filesystem::is_empty(f))
        removeFolder(folder);
    }
  }
}
