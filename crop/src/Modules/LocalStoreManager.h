/*
 * LocalStoreManager.h
 *
 *  Created on: 10.10.2012
 *      Author: gigi
 */

#ifndef LOCALSTOREMANAGER_H_
#define LOCALSTOREMANAGER_H_

#include <fstream>
#include <iostream>

#include "StoreManager.h"
#include "../rapidXML/rapidxml.hpp"
#include "../rapidXML/rapidxml_print.hpp"
#include "../DataManagement/DataBlock.h"


using namespace rapidxml;

class LocalStoreManager : public StoreManager
{
public:
  LocalStoreManager();
  virtual ~LocalStoreManager();

private:
  const std::vector<DataBlock_sPtr>& load();
  void store(DataBlock_sPtr& db);

//  inline const char* stralloc(const std::string& str);
//  inline xml_node<>* node(const std::string& name, const std::string& content = "");

//  xml_document<> doc;
  ByteArray_sPtr DBcontent;
  Timestamp timestamp;
};

#endif /* LOCALSTOREMANAGER_H_ */
