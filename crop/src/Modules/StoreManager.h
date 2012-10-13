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

class StoreManager
{
public:
  virtual ~StoreManager(){};

  virtual const std::vector<DataBlock_sPtr>& load() = 0;
  virtual void store(DataBlock_sPtr& db) = 0;
};

#endif /* STOREMANAGER_H_ */
