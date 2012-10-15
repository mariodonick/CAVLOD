/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/CrodtModule.h"

int main()
{
  CrodtModuleIF* crodt = new CrodtModule;

  crodt->initialize();
  crodt->sendText("hallo welt", true);

  delete crodt;
  return 0;
}
