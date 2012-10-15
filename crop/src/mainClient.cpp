/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/SenderModule.h"
#include "DataManagement/CrodtIO.h"

int main()
{
  crodt::SenderModuleIF* crodt = new crodt::SenderModule;
  crodt->initialize();

  while(true)
  {
  std::string text = "Es folgt ein Beispieltext:\n";
  text.append("Hallo ich bin ein Beispieltext und komme vom Mars.\n");
  text.append("Dabei wurde ich zuerst zerstückelt, dann priorisiert, einzeln versendet und auf der Erde wieder zusammengesetzt.\n");

  crodt::RelevanceData rd0; // = Beispieltext:\n
  rd0.relevanceValue = 100.f;
  rd0.pos.x = 13;
  rd0.pos.y = 0;
  rd0.pos.len_x = 14;

  crodt::RelevanceData rd1; // = Hallo ich
  rd1.relevanceValue = 80.f;
  rd1.pos.x = 0;
  rd1.pos.y = 1;
  rd1.pos.len_x = 9;

  crodt::RelevanceData rd2; // = komme vom Mars.\nDabei
  rd2.relevanceValue = 60.f;
  rd2.pos.x = 35;
  rd2.pos.y = 1;
  rd2.pos.len_x = 22;

  crodt::RelevanceData rd3; // = dann priorisiert,
  rd3.relevanceValue = 30.f;
  rd3.pos.x = 37;
  rd3.pos.y = 2;
  rd3.pos.len_x = 18;

  crodt::RelevanceData rd4; // = und_
  rd4.relevanceValue = 70.f;
  rd4.pos.x = 73;
  rd4.pos.y = 2;
  rd4.pos.len_x = 4;

  crodt::CrodtInput ci;
  ci.is_timestamp = true;
  ci.content = text;
  ci.relevanceVector.push_back(rd0);
  ci.relevanceVector.push_back(rd1);
  ci.relevanceVector.push_back(rd2);
  ci.relevanceVector.push_back(rd3);
  ci.relevanceVector.push_back(rd4);

  crodt->sendText(ci);

  sleep(5);
  }
  delete crodt;
  return 0;
}
