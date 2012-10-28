/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/SenderModule.h"
#include "DataManagement/CrodtIO.h"
#include "Tools/Random.h"

#include <thread>
#include <fstream>

crodt::SenderModuleIF* c;
bool running;

void sensorIn()
{
  while(running)
  {
    sleep(1);
    c->sendSensor(randomDouble(0.0, 100.0));
  }
}

void validation(const std::string& filename)
{
  // if you do the test again change the directory
  std::ifstream file("/home/flo/CAVLOD/validation/"+filename, std::ios::in);
  if( !file.is_open() )
    std::cerr << "error open file: " << filename << "\n";

  file.seekg(0, std::ios::end);
  std::size_t size = file.tellg();
  file.seekg(0, std::ios::beg);

  char* buf = new char[size];
  file.read(buf, size);

  crodt::CrodtInput ci;
  ci.is_timestamp = false;
  ci.content.insert(0, buf, size);

  std::cout << "\nThis file has " << size << " bytes, measuring 10 times...\n";
  for(unsigned int i = 0; i < 10; ++i)
    c->sendText(ci);

  delete[] buf;
}

int main()
{
  randomInitialize();
  c = new crodt::SenderModule;
  c->initialize();

  // validation
  validation("2B.txt");
  validation("10B.txt");
  validation("100B.txt");
  validation("1000B.txt");
  validation("10000B.txt");
  validation("100000B.txt");
  validation("500000B.txt");
  validation("1000000B.txt");
  validation("5000000B.txt");
  validation("10000000B.txt");
  std::cout << "Finished measurement!\n";

  sleep(120);

//   running = true;
//  std::thread sens(&sensorIn); // start sensor thread
//
//  // first test case
//  for(unsigned int i = 0; i < 3; ++i)
//  {
//    std::string text = "Es folgt ein Beispieltext:\n";
//    text.append("Hallo ich bin ein Beispieltext und komme vom Mars.\n");
//    text.append("Dabei wurde ich zuerst zerstückelt, dann priorisiert, einzeln versendet und auf der Erde wieder zusammengesetzt.\n");
//
//    crodt::RelevanceData rd0; // = Beispieltext:\n
//    rd0.relevanceValue = 100.f;
//    rd0.pos.x = 13;
//    rd0.pos.y = 0;
//    rd0.pos.len_x = 14;
//
//    crodt::RelevanceData rd1; // = Hallo ich
//    rd1.relevanceValue = 80.f;
//    rd1.pos.x = 0;
//    rd1.pos.y = 1;
//    rd1.pos.len_x = 9;
//
//    crodt::RelevanceData rd2; // = komme vom Mars.\nDabei
//    rd2.relevanceValue = 60.f;
//    rd2.pos.x = 35;
//    rd2.pos.y = 1;
//    rd2.pos.len_x = 22;
//
//    crodt::RelevanceData rd3; // = dann priorisiert,
//    rd3.relevanceValue = 30.f;
//    rd3.pos.x = 37;
//    rd3.pos.y = 2;
//    rd3.pos.len_x = 18;
//
//    crodt::RelevanceData rd4; // = und_
//    rd4.relevanceValue = 70.f;
//    rd4.pos.x = 73;
//    rd4.pos.y = 2;
//    rd4.pos.len_x = 4;
//
//    crodt::CrodtInput ci;
//    ci.is_timestamp = true;
//    ci.content = text;
//
//    ci.relevanceVector.push_back(rd1);
//    ci.relevanceVector.push_back(rd2);
//    ci.relevanceVector.push_back(rd4);
//    ci.relevanceVector.push_back(rd3);
//    ci.relevanceVector.push_back(rd0);
//
//    c->sendText(ci);
//
//    sleep(5);
//  }
//  running = false;
//
//  if(sens.joinable())
//    sens.join();

  // second test case
//  crodt::CrodtInput ci;
//  ci.is_timestamp = true;
//  ci.content = "hallo welt";
//
//  c->sendText(ci);
//  sleep(11);
//
//  crodt::CrodtInput ci2;
//  ci2.is_timestamp = true;
//  ci2.content = "abcdef";
//  c->sendText(ci2);
//  sleep(20);

  delete c;
  return 0;
}
