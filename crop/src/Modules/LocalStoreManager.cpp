/*
 * LocalStoreManager.cpp
 *
 *  Created on: 10.10.2012
 *      Author: gigi
 */

#include "LocalStoreManager.h"
#include "../TypesConfig/ProtocolTypes.h"
#include "../Tools/ByteArray.h"

#include <string>
#include <stdio.h>
#include <sstream>
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
  while(entry = readdir(dirBasePath))
  {
    dirDoidPath = opendir(doidFolder);
    while(entry = readdir(dirDoidPath))
    {

    }
    closedir(dirDoidPath);
  }
  closedir(dirBasePath);


}

void LocalStoreManager::store(DataBlock_sPtr& db)
{
  DBcontent = db->getContent();

  DBDatatype dataType_uint = db->getDataType().to_uint;
  DBConfig config_uint = db->getConfig().to_uint;
  DBDataObjectID dataObjectID_uint = db->getDataObjectID().to_uint;
  DBSequenceNumber sequenzNumber_uint = db->getSequenceNumber().to_uint;
  DBLength length_uint = db->getLength().to_uint;

  std::stringstream ssDOID;
  ssDOID << dataObjectID_uint;

  std::string baseFolder = "/home/gigi/Desktop/";

  std::stringstream ssSequenzNumber;
  ssSequenzNumber << sequenzNumber_uint;

  std::string file = "binary.bin";

  std:: string finally = baseFolder + ssDOID.str() + ssSequenzNumber.str() + file;

  std::ofstream outbin(finally,std::ios::binary);
  outbin.write(reinterpret_cast <const char*> (&dataType_uint), sizeof(dataType_uint));
  outbin.write(reinterpret_cast <const char*> (&config_uint), sizeof(config_uint));
  outbin.write(reinterpret_cast <const char*> (&dataObjectID_uint), sizeof(dataObjectID_uint));
  outbin.write(reinterpret_cast <const char*> (&sequenzNumber_uint), sizeof(sequenzNumber_uint));
  outbin.write(reinterpret_cast <const char*> (&length_uint), sizeof(length_uint));
  outbin.write(reinterpret_cast <const char*> (&timeStamp_uint), sizeof(timeStamp_uint));
  outbin.write(DBcontent->dataPtr(), sizeof(DBcontent->size()));
  outbin.close();

 /* //Header-Daten
  xml_node<>* header = node("header");
    header->append_node(node("data type",dataType_str));
    header->append_node(node("config",config_str));
    header->append_node(node("DOID",dataObjectID_str));
    header->append_node(node("sequenz number",sequenzNumber_str));
    header->append_node(node("length",length_str));
  doc.append_node(header);*/

}

/*inline const char* LocalStoreManager::stralloc(const std::string& str)
{
  return doc.allocate_string(str.c_str());
}

inline xml_node<>* LocalStoreManager::node(const std::string& name, const std::string& content)
{
  return doc.allocate_node(node_element, stralloc(name), stralloc(content));
}*/
