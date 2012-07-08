/*
 * @brief mainServer.cpp implementation of member functions
 */

#include "Modules/ServerModule.h"

#include <sys/signal.h>
#include <iostream>
#include <unistd.h>

ServerModule* server;

/**
 * Signal Handler for strg+c Interrupt Signal. Will safely call the shutdown function.
 */
void signal_handler_SIGINT (int status)
{
  std::cout << "*************       Received SIGINT signal. ********************\n";
  std::cout << "Info: Stopping Server Modul\n";
  delete server; server = nullptr;
  std::cout << "Info: Stopped  Server Module\n";
  exit(0);
}

int main()
{
  signal(SIGINT, signal_handler_SIGINT);

  server = new ServerModule;
  server->execute();

  return 0;
}


//  unsigned char testData1[] = {
//    0x01, 0x00, // ver + conf
//    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, // SRC
//    0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, // DST
//    0x63, 0x00, 0x00, // msg length = 37 + (9 + 12 + 12) + (9 + 18) + 2 = 0x63
//    //--- 37 byte
//    //------------------------- db 0
//    0x00, 0x00, // dt + conf
//    0x21, 0x43, 0x65, // DOID
//    0xA0, 0x00, // sequ nr = 160
//    0x21, 0x00, // db length = 9 + 12 + 12 = 0x21
//    //---46 byte
//    // content 0
//    0xee, 0xe8, 0x82, 0x02, 0x00, 0x00, 0x00, 0x00, // timestamp 42133742
//    0x00, 0x00, 0x5e, 0x43, // value 222
//    // content 1
//    0xee, 0xe8, 0x82, 0x02, 0x00, 0x00, 0x00, 0x00, // timestamp 42133742
//    0x00, 0x00, 0x5e, 0x43, // value 222
//    //------------------------- db 1
//    // -- 62 byte
//    0x01, 0x00, // dt + conf = TEXT
//    0x21, 0x43, 0x65, // DOID
//    0xA1, 0x00, // sequ nr = 161
//    0x1B, 0x00, // db length = 9 + 18
//    //--- 71 byte
//    // content
//    0xee, 0xe8, 0x82, 0x02, 0x00, 0x00, 0x00, 0x00, // timestamp 42133742
//    0x00, 0x00, // line 0
//    0x4D, 0x41, 0x52, 0x53, 0x53, 0x52, 0x41, 0x4D, // text: MARSSRAM
//    // -- 89 byte
//    0xEB, 0xFE // crc_16
//  };
