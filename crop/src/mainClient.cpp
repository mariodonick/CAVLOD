/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/SenderModule.h"
#include "DataManagement/CrodtIO.h"


//#include <algorithm>

//struct Position
//{
//  uint16 x;
//  uint16 y;
//  uint16 len_x;
//};
//
//struct PositionXCmp
//{
//  bool operator() (Position lhs, Position rhs)
//  {
//    return (lhs.x < rhs.x);
//  }
//};
//
//struct PositionYCmp
//{
//  bool operator() (crodt::Position lhs, crodt::Position rhs)
//  {
//    return (lhs.y<rhs.y);
//  }
//};

int main()
{
//  PositionXCmp tmpX;
//  PositionYCmp tmpY;
//
//  crodt::Position pos0{10, 10, 0};
//  crodt::Position pos1{1, 1, 0};
//  crodt::Position pos2{10, 1, 0};
//  crodt::Position pos3{1, 10, 0};
//  crodt::Position pos4{0, 9, 0};
//  crodt::Position pos5{5, 2, 0};
//  crodt::Position pos6{2, 8, 0};
//  crodt::Position pos7{0, 1, 0};
//  crodt::Position pos8{7, 3, 0};
//  crodt::Position pos9{3, 5, 0};
//  crodt::Position pos10{1, 2, 0};
//  crodt::Position pos11{10, 10, 0};
//
//  std::vector<crodt::Position> vecY;
//  vec.push_back(pos0);
//  vec.push_back(pos3);
//  vec.push_back(pos1);
//  vec.push_back(pos2);
//  vec.push_back(pos4);
//  vec.push_back(pos5);
//  vec.push_back(pos6);
//  vec.push_back(pos7);
//  vec.push_back(pos8);
//  vec.push_back(pos9);
//  vec.push_back(pos10);
//  vec.push_back(pos11);
//
//  std::vector<crodt::Position> vecX;
//
////  std::vector<int> v = {9,2,3,23,5,3,9,5,6,7,8,4,3,6,456};
////  std::sort(v.begin(), v.end());
//
//  std::sort(vec.begin(), vec.end(), tmpY);
////  std::sort(vec.begin(), vec.end(), tmpX);
//
//  std::vector<crodt::Position>::iterator pre = vec.begin();
//  std::vector<crodt::Position>::iterator cur = vec.begin();
//  std::vector<crodt::Position>::iterator last = vec.begin();
//  for(std::vector<crodt::Position>::iterator it = vec.begin(); it != vec.end(); ++it )
//  {
//
//  }
//
//  for(std::vector<crodt::Position>::iterator it = vec.begin(); it != vec.end(); ++it )
//  {
//    std::cout << "x: " << it->x << " y: " << it->y << "\n";
//  }
//}


//  for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it )
//  {
//    std::cout << "x: " << *it << "\n";
//  }

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
