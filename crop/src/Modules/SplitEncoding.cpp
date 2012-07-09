/*
 * @brief SplitEncoding.cpp implementation of member functions
 */

#include "SplitEncoding.h"
#include "Crodm.h"
#include "../DataManagement/Content.h"
#include "../DataManagement/DataTypes.h"
#include "../DataManagement/DataBlock.h"
#include "../Tools/ByteArray.h"
#include "../Tools/Queue.h"

#include <boost/tokenizer.hpp>
#include <sstream>

typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

SplitEncoding::SplitEncoding(const Crodm& theCrodm, Queue<DataBlock*>& theDBFifo)
: crodm(theCrodm)
, dbFifo(theDBFifo)
{
}

SplitEncoding::~SplitEncoding()
{
}

void SplitEncoding::partText( const Bin<24>& doid, const std::string& content )
{
  const std::vector<unsigned short int>& numWords = crodm.getWordLengthVec();

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
      DataBlock::Header dbh;
      dbh.config = 0;
      dbh.dataObjectID = doid;
      dbh.sequenceNumber = sequNr;
      dbh.dataType = TYPE_TEXT;

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

      ByteArray* content = new ByteArray;
      content->insert(text);

      DataBlock* db = new DataBlock;
      db->setHeader( dbh );
      db->addContent( content );

      dbFifo.push(db);
    }
  }
}

void SplitEncoding::partSensor(const Bin<24>& doid, const float& value)
{
  static unsigned int sNr = 0;

  DataBlock::Header dbh;
  dbh.config = 0;
  dbh.dataObjectID = doid;
  dbh.sequenceNumber = ++sNr;
  dbh.dataType = TYPE_SENSOR;

  DataBlock* db = new DataBlock;
  db->setHeader(dbh);

  Sensor sensor;
  sensor.value = value;

  ByteArray* content = new ByteArray;
  content->insert(sensor);
  db->addContent( content );

  dbFifo.push(db);
}
