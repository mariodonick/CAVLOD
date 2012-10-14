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
#include "../Tools/Log.h"
#include "../TypesConfig/Constants.h"

#include <sstream>
#include <list>
#include <cassert>

SplitEncoding::SplitEncoding(const Crodm_uPtr& theCrodm, DBQueue_uPtr& theDBFifo)
: crodm(theCrodm)
, dbFifo(theDBFifo)
{
}

SplitEncoding::~SplitEncoding()
{
}

// todo funktion aufräumen viele code passagen sind nicht unique!!!
void SplitEncoding::partText( const DBDataObjectID& doid, const std::string& content, const bool& usingTimestamp )
{
  const std::vector<RelevanceData>& relevanceData = crodm->getRelevanceData(doid, TYPE_TEXT);

  if(content.size() == 0)
  {
    WARNING() << "you bastard give me an empty content!!!\n";
    return;
  }

  assert(relevanceData.size() > 0);
  assert(content.size() > 0);

  // find and separate lines
  std::vector<std::size_t> linePos;
  linePos.push_back(0);

  std::stringstream ss;
  ss << content;

  // compute the total size length for every line
  unsigned int oldTotalLineSize = 0;
  while( !ss.eof() )
  {
    std::string curLine;
    std::getline(ss, curLine);

    if( !curLine.empty()  )
    {
      unsigned int lineSize = curLine.size() + 1 + oldTotalLineSize; // +1 because last char is the line break
      linePos.push_back( lineSize  );
      oldTotalLineSize = lineSize;
    }
  }

//  for(std::vector<std::size_t>::iterator itL = linePos.begin(); itL != linePos.end(); ++itL)
//    std::cout << "size: " << *itL << "\n";

//  std::cout << "---line preprocessing end-------\n";

  std::list<GlobalPosition> globalPositions;
  std::vector<RelevanceData>::const_iterator r_cur = relevanceData.begin();

  // transform two dimensional coordinates to 1 dimensional
  // and create blocks with relevant informations
  while(r_cur != relevanceData.end())
  {
//    std::cout << "r_cur->pos_x: " << r_cur->pos_x << "\n";
//    std::cout << "r_cur->pos_y: " << r_cur->pos_y << "\n";
//    std::cout << "r_cur->len_x: " << r_cur->len_x << "\n";

    GlobalPosition fragm = transform2global(*r_cur, linePos);
    globalPositions.push_back(fragm);

//    std::cout << "fragm: " << fragm << "\n\n--------------------------\n";
    ++r_cur;
  }

  // compute blocks without relevance by using the current block and the next block with relevant values
//  std::cout << "--------insert zero relevance fragments -----------------\n";

  std::list<GlobalPosition>::iterator curBlock = globalPositions.begin();
  std::list<GlobalPosition>::iterator preBlock = globalPositions.begin();

  for(; curBlock != globalPositions.end(); ++curBlock)
  {
//    std::cout << "curBlock: pos " << curBlock->pos << " len: " << curBlock->length << "\n";
//    std::cout << "preBlock: pos " << preBlock->pos << " len: " << preBlock->length << "\n";
//    std::cout << "zeropos: " << ((curBlock == preBlock) ? 0 : preBlock->pos + preBlock->length) << "\n";
//    std::cout << "zerolength: " << ((curBlock == preBlock) ? curBlock->pos : curBlock->pos - (preBlock->pos + preBlock->length)) << "\n";
    GlobalPosition zero = diffFrom2RelevanceData(preBlock, curBlock);

    if(zero.length != 0)
      globalPositions.insert(curBlock, zero);

    preBlock = curBlock;
//    std::cout << "------------fragment end------\n\n";
  }

  std::list<GlobalPosition>::iterator lastFrag = globalPositions.end();
  --lastFrag;

  // if the last block do not reach the end of the content, this will compute the last block
  if(lastFrag->pos + lastFrag->length < *(linePos.end()-1))
  {
    uint16_t endPos = lastFrag->pos + lastFrag->length;

    GlobalPosition lastZero;
    lastZero.length = *(linePos.end()-1) - endPos;
    lastZero.pos = endPos;
    lastZero.relevance = 0;

    globalPositions.push_back(lastZero);
//    std::cout << "lastZero: " << lastZero << "\n";
  }
//  std::cout << "\n";

//  for(std::list<GlobalPosition>::iterator it = globalPositions.begin(); it != globalPositions.end(); ++it)
//    std::cout << "it: " << *it << "\n";
//
//  std::cout << "\n";

  // check if all datablocks have the correct size... otherwise we split this
  for(std::list<GlobalPosition>::iterator it = globalPositions.begin(); it != globalPositions.end(); ++it)
  {
//    std::cout << "------------ new iteration ---------------\n";
    const std::size_t dbConstSize = C_LINE_BYTES + C_COLUMN_BYTES + DB_HEADER_LENGTH_BYTES + (usingTimestamp ? C_TIMESTAMP_BYTES : 0);
    const std::size_t maxTextSize = MAX_DB_LENGTH - dbConstSize;

//    std::cout << "dbconstsize: " << dbConstSize << "\n";
//    std::cout << "maxSize: " << maxTextSize << "\n";
//    std::cout << "it: " << (*it) << "\n";

    if( it->length > maxTextSize )
    {
//      std::cout << "\n--------------------------------- if ----------------------------\n";

      const std::size_t numParts = it->length/maxTextSize;
      const std::size_t lastPart = it->length % maxTextSize;

//      std::cout << "numParts: " << numParts << "\n";
//      std::cout << "lastPart: " << lastPart << "\n";

      for(unsigned int i = 0; i < numParts; ++i)
      {
        GlobalPosition tmp;
        tmp.relevance = it->relevance;
        tmp.length = maxTextSize;
        tmp.pos = it->pos + maxTextSize*i;

//        std::cout << "tmp: " << tmp << "\n";
        globalPositions.insert(it, tmp);
      }

      if(lastPart != 0)
      {
        GlobalPosition tmp;
        tmp.relevance = it->relevance;
        tmp.length = lastPart;
        tmp.pos = it->pos + maxTextSize*numParts;

//        std::cout << "last part tmp: " << tmp << "\n";

        globalPositions.insert(it, tmp);
      }
      std::list<GlobalPosition>::iterator tmp_it = it;
      ++it;
      globalPositions.erase(tmp_it);

//      std::cout << "\n------------------------------- end if --------------------------\n";
    }
  }

  // create datablocks
  unsigned int sequNr = 0;
  for(std::list<GlobalPosition>::iterator it = globalPositions.begin(); it != globalPositions.end(); ++it)
  {
//    std::cout << "\n-------------------------------------\n";
    DataBlock::Header dbh;
    dbh.config = 0;
    dbh.dataObjectID = doid;
    dbh.sequenceNumber = sequNr++;
    dbh.dataType = TYPE_TEXT;
    dbh.config[DB_CONFIG_TIMESTAMP_INDEX] = usingTimestamp;

    DataBlock_sPtr db(new DataBlock);
    db->setHeader(dbh);
    db->stamp();

    Text text;
    text.text = content.substr(it->pos, it->length);
    RelevanceData rel_tmp = transform2localRelData(*it, linePos);
    text.line = rel_tmp.pos_y;
    text.column = rel_tmp.pos_x;

//    std::cout << "text size: " << text.text.size() << " + 4 fuer line und column\n";
//    std::cout << "text: " << text.text << "\n";
//    std::cout << "line: " << text.line.to_uint() << "\n";
//    std::cout << "column: " << text.column.to_uint() << "\n";

    ByteArray_sPtr content(new ByteArray);
    content->insert(text);
    db->addContent( content );
    db->setRelevanceData( rel_tmp );

//    std::cout << "db length: " << db->getLength().to_uint() << "\n";

    dbFifo->push(db);
  }
}

void SplitEncoding::partSensor(const DBDataObjectID& doid, const float& value, const bool& usingTimestamp)
{
  static unsigned int sNr = 0;

  // todo was soll man hier damit machen??? O.o
//  const std::vector<RelevanceData>& relevanceData = crodm->getRelevanceData(doid, TYPE_SENSOR);

  DataBlock::Header dbh;
  dbh.config = 0;
  dbh.dataObjectID = doid;
  dbh.sequenceNumber = sNr++;
  dbh.dataType = TYPE_SENSOR;
  dbh.config[DB_CONFIG_TIMESTAMP_INDEX] = usingTimestamp;

  Sensor sensor;
  sensor.value = value;

  DataBlock_sPtr db( new DataBlock );
  db->setHeader(dbh);
  db->stamp();

//  std::cout << "timestamp: " << db.getTimestamp().to_ulong() << " = 0x" << std::hex << db.getTimestamp().to_ulong() << std::dec << "\n";

  ByteArray_sPtr content(new ByteArray);
  content->insert(sensor);
  db->addContent( content );

  dbFifo->push(db);
}

const RelevanceData SplitEncoding::transform2localRelData(const SplitEncoding::GlobalPosition& gp, const std::vector<std::size_t>& len)
{
  unsigned int index = 0;
  for(unsigned int i = 0; i < len.size(); ++i)
  {
    if( int(gp.pos - len[i]) < 0 )
    {
      index = i-1;
      break;
    }
  }

  RelevanceData rel;
  rel.len_x = gp.length;
  rel.pos_x = gp.pos - len[index];
  rel.pos_y = index;
  rel.relevanceValue = gp.relevance;

  return rel;
}

const SplitEncoding::GlobalPosition SplitEncoding::transform2global(const RelevanceData& r, const std::vector<std::size_t>& len)
{
  GlobalPosition gp;
  gp.length = r.len_x;
  gp.pos = r.pos_x + len[r.pos_y];
  gp.relevance = r.relevanceValue;

  return gp;
}

// computes the global position between two blocks
const SplitEncoding::GlobalPosition SplitEncoding::diffFrom2RelevanceData(
    const std::list<GlobalPosition>::iterator& pre,
    const std::list<GlobalPosition>::iterator& cur)
{
  GlobalPosition gp;
  gp.pos = (cur == pre) ? 0 : pre->pos + pre->length;
  gp.length = (cur == pre) ? cur->pos : cur->pos - (pre->pos + pre->length);
  gp.relevance = 0;

  return gp;
}

std::ostream& operator<<(std::ostream& out, const SplitEncoding::GlobalPosition& gp)
{
  out << "pos: " << gp.pos
      << " length: " << gp.length
      << " relevance: " << gp.relevance;
  return out;
}
