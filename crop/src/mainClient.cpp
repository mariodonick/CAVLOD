/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/ClientModule.h"

#include <sys/signal.h>
#include <iostream>
//#include <vector>

ClientModule* client;

/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
void signal_handler_SIGINT (int status)
{
  std::cout << "*************       Received SIGINT signal. ********************\n";
  std::cout << "Info: Stopping Client Modul\n";
  delete client; client = nullptr;
  std::cout << "Info: Stopped  client Module\n";
  exit(0);
}

//struct GlobalPosition
//{
//  uint16_t pos;
//  uint16_t length;
////  float relevance;
////  uint16_t line;
////  uint16_t column;
////  RelevanceData relevanceData;
//
//  friend std::ostream& operator<<(std::ostream& out, const GlobalPosition& frag)
//  {
//    out << "pos: " << frag.pos
//        << " length: " << frag.length;
////        << " relevance: " << frag.relevance
////        << " line: " << frag.line
////        << " column: " << frag.column;
//    return out;
//  }
//};
//
//struct LocalPosition
//{
////  float relevanceValue;
//  uint16_t pos_x;
//  uint16_t pos_y;
//  uint16_t len_x;
////  uint16_t len_y;
//
//  friend std::ostream& operator<<(std::ostream& out, const LocalPosition& rel)
//  {
//    out
////    << "relevance: " << rel.relevanceValue
//        << " pos_x: " << rel.pos_x
//        << " pos_y: " << rel.pos_y
//        << " len_x: " << rel.len_x;
////        << " len_y: " << rel.len_y;
//    return out;
//  }
//};
//
//GlobalPosition transform2global(LocalPosition lp, std::vector<unsigned int>& len)
//{
//  GlobalPosition gp;
//  gp.length = lp.len_x;
//  gp.pos = lp.pos_x + len[lp.pos_y];
//
//  return gp;
//}
//
//LocalPosition transform2local(GlobalPosition gp, std::vector<unsigned int>& len)
//{
//  unsigned int index = 0;
//  for(unsigned int i = 0; i < len.size(); ++i)
//  {
//    if( int(gp.pos - len[i]) < 0 )
//    {
//      index = i-1;
//      break;
//    }
//  }
//
//  std::cout << "index: " << index << "\n";
//  LocalPosition lp;
//  lp.len_x = gp.length;
//  lp.pos_x = gp.pos - len[index];
//  lp.pos_y = index;
//
//  return lp;
//}



int main()
{
//  std::vector<unsigned int> linelen = {0, 27, 78, 192};
//
//  LocalPosition lp1 = {0,0,13};
//  std::cout << "lp1: " << lp1 << "\n";
//  GlobalPosition gp1 = transform2global(lp1, linelen);
//  std::cout << "transform2global: gp1: " << gp1 << "\n";
//  LocalPosition lp1_ = transform2local(gp1, linelen);
//  std::cout << "transform2local: lp1_: " << lp1_ << "\n\n";
//
//  LocalPosition lp2 = {13,0,14};
//  std::cout << "lp2: " << lp2 << "\n";
//  GlobalPosition gp2 = transform2global(lp2, linelen);
//  std::cout << "transform2global: gp2: " << gp2 << "\n";
//  LocalPosition lp2_ = transform2local(gp2, linelen);
//  std::cout << "transform2local: lp2_: " << lp2_ << "\n\n";
//
//  LocalPosition lp3 = {0,1,9};
//  std::cout << "lp3: " << lp3 << "\n";
//  GlobalPosition gp3 = transform2global(lp3, linelen);
//  std::cout << "transform2global: gp3: " << gp3 << "\n";
//  LocalPosition lp3_ = transform2local(gp3, linelen);
//  std::cout << "transform2local: lp3_: " << lp3_ << "\n\n";
//
//  LocalPosition lp4 = {9,1,25};
//  std::cout << "lp4: " << lp4 << "\n";
//  GlobalPosition gp4 = transform2global(lp4, linelen);
//  std::cout << "transform2global: gp4: " << gp4 << "\n";
//  LocalPosition lp4_ = transform2local(gp4, linelen);
//  std::cout << "transform2local: lp4_: " << lp4_ << "\n\n";
//
//  LocalPosition lp5 = {35,1,22};
//  std::cout << "lp5: " << lp5 << "\n";
//  GlobalPosition gp5 = transform2global(lp5, linelen);
//  std::cout << "transform2global: gp5: " << gp5 << "\n";
//  LocalPosition lp5_ = transform2local(gp5, linelen);
//  std::cout << "transform2local: lp5_: " << lp5_ << "\n\n";
//
//  LocalPosition lp6 = {6,2,30};
//  std::cout << "lp6: " << lp6 << "\n";
//  GlobalPosition gp6 = transform2global(lp6, linelen);
//  std::cout << "transform2global: gp6: " << gp6 << "\n";
//  LocalPosition lp6_ = transform2local(gp6, linelen);
//  std::cout << "transform2local: lp6_: " << lp6_ << "\n\n";
//
//  LocalPosition lp7 = {32,2,18};
//  std::cout << "lp7: " << lp7 << "\n";
//  GlobalPosition gp7 = transform2global(lp7, linelen);
//  std::cout << "transform2global: gp7: " << gp7 << "\n";
//  LocalPosition lp7_ = transform2local(gp7, linelen);
//  std::cout << "transform2local: lp7_: " << lp7_ << "\n\n";
//
//  LocalPosition lp8 = {55,2,18};
//  std::cout << "lp8: " << lp8 << "\n";
//  GlobalPosition gp8 = transform2global(lp8, linelen);
//  std::cout << "transform2global: gp8: " << gp8 << "\n";
//  LocalPosition lp8_ = transform2local(gp8, linelen);
//  std::cout << "transform2local: lp8_: " << lp8_ << "\n\n";


  signal(SIGINT, signal_handler_SIGINT);

  client = new ClientModule;
  client->start();

  while (true) sleep(300);
  return 0;
}
