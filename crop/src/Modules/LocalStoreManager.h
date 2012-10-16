/*
 * LocalStoreManager.h
 *
 *  Created on: 10.10.2012
 *      Author: gigi
 */

#ifndef LOCALSTOREMANAGER_H_
#define LOCALSTOREMANAGER_H_

#include "StoreManager.h"
#include "../DataManagement/DataBlock.h"

namespace crodt
{

class Config;

class LocalStoreManager : public StoreManager
{
public:
  LocalStoreManager();
  virtual ~LocalStoreManager();

private:
  const std::vector<DataBlock_sPtr>& load();
  void store(const DataBlock_sPtr& db);
  void remove(const DataBlock::Header& dbh);

private:
  std::vector<DataBlock_sPtr> dbVec;
  Config& config;
};

} // namespace crodt

#endif /* LOCALSTOREMANAGER_H_ */
