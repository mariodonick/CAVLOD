/*
 * @brief mainServer.cpp implementation of member functions
 */

#include "Modules/ServerModule.h"

#include "Modules/SplitEncoding.h"
#include "Modules/Priority.h"
#include "Modules/MessagePacketizer.h"
#include "Modules/MessageParser.h"
#include "Tools/Fifo.h"
#include "Tools/PrioritizedQueue.h"
#include "Tools/ByteArray.h"
#include "Modules/OntologyFacade.h"
#include "Modules/UDPSocket.h"

int main()
{
  ServerModule earth;
  earth.execute();

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

//  Queue<ByteArray*>* fifo = new Fifo<ByteArray*>;
//  PrioritizedQueue prioQueue;
//  Ontology* ontology = new OntologyFacade;
////                           |              |             |                    |   |
//  std::string text = "Ich war";// (heute Mittag) in der Mensa, wo es Fisch gab; der war viel zu trocken.";
//  Partitioning* part = new SplitEncoding(*ontology, *fifo);
//  Prioritization* prio = new Priority(*fifo, prioQueue, *ontology);
//  Packetizer* packetizer = new MessagePacketizer(prioQueue);
//
//  std::vector<unsigned short int> vec = {2};//, 2, 3, 5, 1, 5, 6};
//  part->partText(1, text);
//  prio->evaluate();
//  ByteArray arr = packetizer->packetizeMessage();
//
//  // -------------- mars --------------
//  // -------------- weltraum start --------------
//
//  std::cout << "weltraum dump: \n";
//  arr.dumpHex(std::cout);
//
//  // -------------- weltraum ende --------------
//  // -------------- erde --------------
//
//  Parser* parser = new MessageParser;
//  parser->parse(arr);






//  ByteArray b;
//  Sensor s;
//  s.stamp();
//  s.value = 222;
//
//  Text t;
//  t.stamp();
//  t.line = 0x7FFE;
//  t.text = "ABC";
//
//  DataBlock<Text> db;
//  DataBlockHeader dbh;
////  dbh.setConfig(0xFF);
////  dbh.setDataObjectID(0x123456);
////  dbh.setDataType(0xF1F);
////  dbh.setSequenceNumber(0x99);
////  db.addContent(&t, t.size());
////  dbh.setConfig(0xFF);
////  dbh.setDataObjectID(0xFFFFFF);
////  dbh.setDataType(0xFFF);
////  dbh.setSequenceNumber(0xFFFF);
////  db.addContent(&t, t.size());
////  dbh.setLength(DB_HEADER_LENGTH_BYTES+13);
////  db.setHeader(dbh);
//
//
//  b.insert(db);
////  b.append(t);
//  std::cout << "test dump: " << "\n";
//  b.dumpHex(std::cout);
//  b.dumpBin(std::cout);
//
//  std::cout << "size sensor: " << sizeof(Sensor)<< "\n";
//  std::cout << "size text: " << sizeof(Text)<< "\n";
//
////  char d[99];
////  for(unsigned int i = 0; i < 99; ++i)
////    d[i] = testData1[i];
//
//
//  NetworkIO* network = new UDPSocket;
//  network->startServer(5680);
//
//
////  while(true)
////  {
////    std::cout << "receive data\n";
////    const ByteArray* net = network->receiveData();
////    if(net->size() != 0)
////      net->dumpHex(std::cout);
////
////    delete net;
////  }


//  Bin<10> bin0 = 0x201;
//  Bin<5> bin1 = 0x11;
//  Bin<18> bin2 = 0x20001;
//  Bin<64> bin3 = 0x40000000000000001;
//
//  ByteArray array;
//  array.insert(bin0);
//  array.dumpBin(std::cout);
//  array.append(bin1);
//  array.dumpBin(std::cout);
//  array.append(bin2);
//  array.dumpBin(std::cout);
//  array.append(bin3);
//
//  array.dumpBin(std::cout);
//  array.dumpHex(std::cout);

//  ByteArray arr;
//  arr.insert(testData1, sizeof(testData1));
//
//  arr.dumpHex(std::cout);
//  arr.dumpBin(std::cout);
//
//  Parser* parser = new MessageParser;
//  parser->parse(arr);
//  delete parser;
//
//  std::cout << "\n---------------------------------------------------------------------------\n\n";
//
//  std::string content = std::string("Hallo Mars\n"
//      "Ich war (heute Mittag) in der Mensa, wo es Fisch gab; der war viel zu trocken.");
//  std::vector<unsigned short int> lengths = {2, 2, 3, 5, 1, 5, 6};
//
//  for(std::vector<unsigned short int>::iterator it = lengths.begin(); it != lengths.end(); ++it)
//    std::cout << *it << " ";
//  std::cout << "\n";
//
//  Queue<ByteArray*>* fifo = new Fifo<ByteArray*>;
//  Partitioning* part = new SplitEncoding(*fifo);
//  part->partText(20, lengths, content);
//  delete part;
//
//  while( !fifo->isEmpty() )
//  {
//    ByteArray* barr = fifo->pop();
//    std::cout << "fifo inhalt: ";
//    barr->dumpHex(std::cout);
//    std::cout << "\n";
//  }
//  delete fifo;

	return 0;
}
