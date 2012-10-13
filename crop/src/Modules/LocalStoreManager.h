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
#include "../DataManagement/DataBlock.h"


class LocalStoreManager : public StoreManager
{
public:
  LocalStoreManager();
  virtual ~LocalStoreManager();

private:
  const std::vector<DataBlock_sPtr>& load();
  void store(DataBlock_sPtr& db);

  std::vector<DataBlock_sPtr> dbVec;
};

#endif /* LOCALSTOREMANAGER_H_ */
