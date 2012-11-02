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
//    c->sendSensor(randomDouble(0.0, 100.0));
    c->sendSensor(50.f);
  }
}

void validationSpeed(const std::string& filename, const bool& fresh)
{
  // if you make the test again change the directory
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
  {
    if(fresh)
    {
      c = new crodt::SenderModule;
      c->sendText(ci);
      delete c;
      usleep(100*1000);
    }
    else
      c->sendText(ci);
  }

  delete[] buf;
  file.close();
}

void validRelevance(const unsigned int& numRelParts, const bool& fresh)
{
  // if you make the test again change the directory
  std::ifstream file("/home/flo/CAVLOD/validation/5000000B.txt", std::ios::in);
  if( !file.is_open() )
    std::cerr << "error open file: " << "/home/flo/CAVLOD/validation/5000000B.txt" << "\n";

  file.seekg(0, std::ios::end);
  std::size_t size = file.tellg();
  file.seekg(0, std::ios::beg);

  char* buf = new char[size];
  file.read(buf, size);

  std::vector<crodt::RelevanceData> rv;

  if(numRelParts < 5)
  {
    crodt::RelevanceData tmp;
    tmp.pos.x = 20000;
    tmp.pos.y = 2;
    tmp.pos.len_x = 30000;
    tmp.relevanceValue = 50.f;
    rv.push_back(tmp);
  }
  else
  {
    unsigned int partsPerLine = numRelParts / 5;
    unsigned int lengthPerLine = (100000 / partsPerLine / 2);

    for(unsigned int line = 0; line < 5; ++line)
    {
      for(unsigned int c = 0; c < 100000; c+= 2*lengthPerLine)
      {
        crodt::RelevanceData tmp;
        tmp.pos.x = c;
        tmp.pos.y = line;
        tmp.pos.len_x = lengthPerLine;
        tmp.relevanceValue = randomDouble(0.0, 100.0);
        rv.push_back(tmp);
      }
    }
  }

  crodt::CrodtInput ci;
  ci.is_timestamp = false;
  ci.content.insert(0, buf, size);
  ci.relevanceVector = rv;

  std::cout << "\nThe relevance Vector contains " << rv.size() << " Elements (planned relevanceparts: " << numRelParts << ").\n";
  std::cout << "This file has " << size << " bytes, measuring 10 times...\n";
  for(unsigned int i = 0; i < 10; ++i)
  {
    if(fresh)
    {
      c = new crodt::SenderModule;
      c->sendText(ci);
      delete c;
      usleep(100*1000);
    }
    else
      c->sendText(ci);
  }

  delete[] buf;
  file.close();
}

void measureFresh()
{
  std::cout << "\nstart measuring fresh\n";
  validationSpeed("2B.txt", true);
  validationSpeed("10B.txt", true);
  validationSpeed("100B.txt", true);
  validationSpeed("1000B.txt", true);
  validationSpeed("10000B.txt", true);
  validationSpeed("100000B.txt", true);
  validationSpeed("500000B.txt", true);
  validationSpeed("1000000B.txt", true);
  validationSpeed("5000000B.txt", true);
  validationSpeed("10000000B.txt", true);

  std::cout << "\nMeasure Relevance!\n";

  validRelevance(1, true);
  validRelevance(5, true);
  validRelevance(10, true);
  validRelevance(50, true);
  validRelevance(100, true);
  validRelevance(500, true);
  validRelevance(1000, true);
  std::cout << "Finished measurement fresh!\n\n";
}

void measureNormal()
{
  std::cout << "\nstart measuring normal\n";
  c = new crodt::SenderModule;
  validationSpeed("2B.txt", false);
  validationSpeed("10B.txt", false);
  validationSpeed("100B.txt", false);
  validationSpeed("1000B.txt", false);
  validationSpeed("10000B.txt", false);
  validationSpeed("100000B.txt", false);
  validationSpeed("500000B.txt", false);
  validationSpeed("1000000B.txt", false);
  validationSpeed("5000000B.txt", false);
  validationSpeed("10000000B.txt", false);

  std::cout << "\nMeasure Relevance!\n";

  validRelevance(1, false);
  validRelevance(5, false);
  validRelevance(10, false);
  validRelevance(50, false);
  validRelevance(100, false);
  validRelevance(500, false);
  validRelevance(1000, false);
  delete c;
  std::cout << "Finished measurement normal!\n\n";
}

int main()
{
  randomInitialize();

  // measurments for PA
//  measureFresh(); // recreates a new sendermodul for every test iteration
//  sleep(2);
  measureNormal(); // creates the sender module once
  sleep(5);

  // for debugging
//  c = new crodt::SenderModule;
//  c->initialize();
//
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
//
//  delete c;
  return 0;
}
