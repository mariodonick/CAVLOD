/*
 * @brief SplitEncoding.cpp implementation of member functions
 */

#include "SplitEncoding.h"
#include "Ontology.h"
#include "../DataManagement/Content.h"
#include "../DataManagement/DataBlockHeader.h"
#include "../DataManagement/DataBlock.h"
#include "../DataManagement/DataTypes.h"
#include "../Tools/ByteArray.h"
#include "../Tools/Queue.h"

#include <boost/tokenizer.hpp>
#include <sstream>

typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

SplitEncoding::SplitEncoding(const Ontology& theOntology, Queue<ByteArray*>& theQueue)
: ontology(theOntology)
, queue(theQueue)
{
}

SplitEncoding::~SplitEncoding()
{
}

void SplitEncoding::partText( const Bin<24>& doid, const std::string& content )
{
  const std::vector<unsigned short int>& numWords = ontology.getWordLengthVec();

  boost::char_separator<char> sep(" ");
  std::stringstream ss;
  ss << content;

  unsigned int sequNr = 0;
  while( !ss.eof() )
  {
    std::string curLine;
    std::getline(ss, curLine);

    Tokenizer tok(curLine, sep);
//    for(Tokenizer::iterator t = tok.begin(); t != tok.end(); ++t)
//      std::cout << *t << "\n";

    unsigned int tokenPos = 0;
    bool tokenEmpty = false;
    for(std::vector<unsigned short int>::const_iterator length = numWords.begin(); length != numWords.end() && !tokenEmpty; ++length)
    {
      DataBlockHeader dbh;
      dbh.setConfig(0);
      dbh.setDataObjectID(doid);
      dbh.setSequenceNumber(sequNr);
      dbh.setDataType(TYPE_TEXT);

      DataBlock<Text> db;
      db.setHeader(dbh);

      Text text;
      text.stamp();
      unsigned short int num = 0;

      Tokenizer::iterator word = tok.begin();
      std::advance(word, tokenPos);
      for(; word != tok.end() && num < *length; )
      {
//        std::cout << "it != tok.end()? " << ((word != tok.end())?"true":"false") << "\n";
//        std::cout << "num < *length? " << ((num < *length)?"true":"false") << "\n";
//        std::cout << "words num: " << num << "\n";
//        std::cout << "length: " << *length << "\n";
//        std::cout << "sequNr: " << sequNr << "\n";
//        std::cout << "current word: " << *word << "\n";

        text.text.append(*word);

        if(word == tok.end())
          text.lineBreak = true;
        else
          text.lineBreak = false;


        if(num < *length - 1) // nur einfügen wenn danach noch wörter kommen
        {
          text.text.append(" ");
//          std::cout << "insert space\n";
        }
//        else
//          std::cout << "skip space\n";

        ++num;
        ++word;
        tokenEmpty = word == tok.end();
//        std::cout << "empty? " << ((tokenEmpty==true)?"true":"false") << "\n";
      }
//      std::cout << "ende tokenizer\n";
      std::cout << "-------------text: " << text.text << "\n";
      ++sequNr;
      tokenPos += *length;

      db.addContent(&text, text.size());

       ByteArray* byteArr = new ByteArray;
       byteArr->insert(db);
       queue.push(byteArr);
    }
  }

}

void SplitEncoding::partSensor(const Bin<24>& doid, const float& value)
{
  static unsigned int sNr = 0;

  DataBlockHeader dbh;
  dbh.setConfig(0);
  dbh.setDataObjectID(doid);
  dbh.setSequenceNumber(++sNr);
  dbh.setDataType(TYPE_SENSOR);

  DataBlock<Sensor> db;
  db.setHeader(dbh);

  Sensor sensor;
  sensor.value = value;
  db.addContent( &sensor, sensor.size() );

//        ByteArray* byteArr = new ByteArray; todo
      //todo insert des DB in byte array
      //todo noch in fifo schieben
}
