/*
 * StoreManager.h
 *
 *  Created on: 10.10.2012
 *      Author: gigi
 */

#ifndef STOREMANAGER_H_
#define STOREMANAGER_H_

#include <vector>
#include "../DataManagement/DataBlock.h"

namespace crodt
{

class StoreManager
{
public:
  virtual ~StoreManager(){};

  virtual const std::vector<DataBlock_sPtr>& load() = 0;
  virtual void store(const DataBlock_sPtr& db) = 0;
  virtual void remove(const DataBlock::Header& dbh) = 0;
};

} // namespace crodt

#endif /* STOREMANAGER_H_ */
