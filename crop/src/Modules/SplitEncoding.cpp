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
#include <list>

typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
struct Fragment
{
  uint16_t pos;
  uint16_t length;
  float relevance;

  uint16_t line;
  uint16_t column;

  friend std::ostream& operator<<(std::ostream& out, const Fragment& frag)
  {
    out << "pos: " << frag.pos
        << " length: " << frag.length
        << " relevance: " << frag.relevance
        << " line: " << frag.line
        << " column: " << frag.column;
    return out;
  }
//  bool operator<(const Fragment& rhs)
//  {
//    return (pos < rhs.pos);
//  }
};

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
  const std::vector<RelevanceData>& relevanceData = crodm.getRelevanceVec();

  assert(relevanceData.size() > 0);
  assert(content.size() > 0);

  // find and separate lines
  std::vector<std::size_t> linePos;
  linePos.push_back(0);

  std::stringstream ss;
  ss << content;

  unsigned int oldTotalLineSize = 0;
  while( !ss.eof() )
  {
    std::string curLine;
    std::getline(ss, curLine);

    if( !curLine.empty()  )
    {
      curLine.append("\n");

      unsigned int lineSize = curLine.size() + oldTotalLineSize;
      linePos.push_back( lineSize  );
      oldTotalLineSize = lineSize;
    }
  }

  for(std::vector<std::size_t>::iterator itL = linePos.begin(); itL != linePos.end(); ++itL)
    std::cout << "size: " << *itL << "\n";

  std::cout << "---line preprocessing end-------\n";

  std::list<Fragment> fragments;
  std::vector<RelevanceData>::const_iterator r_cur = relevanceData.begin();

  while(r_cur != relevanceData.end())
  {
    std::cout << "r_cur->pos_x: " << r_cur->pos_x << "\n";
    std::cout << "r_cur->pos_y: " << r_cur->pos_y << "\n";
    std::cout << "r_cur->len_x: " << r_cur->len_x << "\n";
    std::cout << "r_cur->len_y: " << r_cur->len_y << "\n";

    unsigned int lineStartPos = linePos[r_cur->pos_y];
    std::cout << "lineStartPos: " << lineStartPos << "\n\n";

    Fragment fragm;
    fragm.pos = lineStartPos + r_cur->pos_x;
    fragm.length = r_cur->len_x;
    fragm.relevance = r_cur->relevanceValue;
    fragm.line = r_cur->pos_y;
    fragm.column = r_cur->pos_x;

    fragments.push_back(fragm);
    std::cout << "fragm: " << fragm << "\n\n--------------------------\n";
    ++r_cur;
  }

  // compute blocks without relevance
  std::cout << "--------insert zero relevance fragments -----------------\n";

  std::list<Fragment>::iterator curFrag = fragments.begin();
  std::list<Fragment>::iterator preFrag = fragments.begin();

  for(; curFrag != fragments.end(); ++curFrag)
  {
    std::cout << "curFrag: pos " << curFrag->pos << " len: " << curFrag->length << "\n";
    std::cout << "preFrag: pos " << preFrag->pos << " len: " << preFrag->length << "\n";
    std::cout << "zeropos: " << ((curFrag == preFrag) ? 0 : preFrag->pos + preFrag->length) << "\n";
    std::cout << "zerolength: " << ((curFrag == preFrag) ? curFrag->pos : curFrag->pos - (preFrag->pos + preFrag->length)) << "\n";
    Fragment zero;
    zero.pos = (curFrag == preFrag) ? 0 : preFrag->pos + preFrag->length;
    zero.length = (curFrag == preFrag) ? curFrag->pos : curFrag->pos - (preFrag->pos + preFrag->length);
    zero.relevance = 0;
    zero.line = /*(curFrag->line == preFrag->line) ?*/ preFrag->line; // todo else fall ist noch nicht richtig
    zero.column = zero.pos - linePos[zero.line];

    if(zero.length != 0)
      fragments.insert(curFrag, zero);

    preFrag = curFrag;
    std::cout << "------------fragment end------\n\n";
  }

  std::list<Fragment>::iterator lastFrag = fragments.end();
  --lastFrag;

  // if the last block reach not the end of the content this will compute the last block
  uint16_t endPos = lastFrag->pos + lastFrag->length;
  if(lastFrag->pos + lastFrag->length < *(linePos.end()-1))
  {
    std::cout << "insert last fragment\n";
    Fragment lastZero;
    lastZero.length = *(linePos.end()-1) - endPos;
    lastZero.pos = endPos;
    lastZero.relevance = 0;
    lastZero.line = linePos.size()-2;
    lastZero.column = endPos - linePos[lastZero.line];

    fragments.push_back(lastZero);
    std::cout << "lastZero: " << lastZero << "\n";
  }

  for(std::list<Fragment>::iterator it = fragments.begin(); it != fragments.end(); ++it)
    std::cout << "it: " << *it << "\n";

  // create datablocks
  unsigned int sequNr = 0;
  for(std::list<Fragment>::iterator it = fragments.begin(); it != fragments.end(); ++it)
  {
    DataBlock::Header dbh;
    dbh.config = 0;
    dbh.dataObjectID = doid;
    dbh.sequenceNumber = sequNr++;
    dbh.dataType = TYPE_TEXT;

    DataBlock* db = new DataBlock;
    db->setHeader(dbh);

    Text text;
    text.text = content.substr(it->pos, it->length);
    text.line = it->line;
    text.column = it->column;

    std::cout << "text: " << text.text << "\n";

    ByteArray* content = new ByteArray;
    content->insert(text);
    db->addContent( content );
    db->setRelevance( it->relevance );

    dbFifo.push(db);
  }

  std::cout << "-------text wurde partitioniert!-----------\n";
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

// the way of simplicity =)
//void SplitEncoding::partText( const Bin<24>& doid, const std::string& content )
//{
//const std::vector<RelevanceData>& numWords = crodm.getRelevanceVec();
//
//boost::char_separator<char> sep(" ");
//std::stringstream ss;
//ss << content;
//
//unsigned int sequNr = 0;
//while( !ss.eof() )
//{
//  std::string curLine;
//  std::getline(ss, curLine);
//
//  Tokenizer tok(curLine, sep);
////    for(Tokenizer::iterator t = tok.begin(); t != tok.end(); ++t)
////      std::cout << *t << "\n";
//
//  unsigned int tokenPos = 0;
//  bool tokenEmpty = false;
//  for(std::vector<RelevanceData>::const_iterator length = numWords.begin(); length != numWords.end() && !tokenEmpty; ++length)
//  {
//    DataBlock::Header dbh;
//    dbh.config = 0;
//    dbh.dataObjectID = doid;
//    dbh.sequenceNumber = sequNr;
//    dbh.dataType = TYPE_TEXT;
//
//    Text text;
//    text.stamp();
//    unsigned short int num = 0;
//
//    Tokenizer::iterator word = tok.begin();
//    std::advance(word, tokenPos);
//    for(; word != tok.end() && num < *length; )
//    {
////        std::cout << "it != tok.end()? " << ((word != tok.end())?"true":"false") << "\n";
////        std::cout << "num < *length? " << ((num < *length)?"true":"false") << "\n";
////        std::cout << "words num: " << num << "\n";
////        std::cout << "length: " << *length << "\n";
////        std::cout << "sequNr: " << sequNr << "\n";
////        std::cout << "current word: " << *word << "\n";
//
//      text.text.append(*word);
//
//      if(word == tok.end())
//        text.lineBreak = true;
//      else
//        text.lineBreak = false;
//
//
//      if(num < *length - 1) // nur einfügen wenn danach noch wörter kommen
//      {
//        text.text.append(" ");
////          std::cout << "insert space\n";
//      }
////        else
////          std::cout << "skip space\n";
//
//      ++num;
//      ++word;
//      tokenEmpty = word == tok.end();
////        std::cout << "empty? " << ((tokenEmpty==true)?"true":"false") << "\n";
//    }
////      std::cout << "ende tokenizer\n";
//    std::cout << "-------------text: " << text.text << "\n";
//    ++sequNr;
//    tokenPos += *length;
//
//    ByteArray* content = new ByteArray;
//    content->insert(text);
//
//    DataBlock* db = new DataBlock;
//    db->setHeader( dbh );
//    db->addContent( content );
//
//    dbFifo.push(db);
//  }
//}
