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
#include <algorithm>

using namespace crodt;

SplitEncoding::SplitEncoding(const Crodm_uPtr& theCrodm, DBQueue_uPtr& theDBFifo)
: crodm(theCrodm)
, dbFifo(theDBFifo)
{
}

SplitEncoding::~SplitEncoding()
{
}

void SplitEncoding::partText( const DBDataObjectID& doid, const std::string& content, const bool& usingTimestamp )
{
  const std::vector<RelevanceData>& relevanceData = crodm->getRelevanceData(doid, TYPE_TEXT);

  if(content.size() == 0)
  {
    WARNING() << "The content ist empty!!!\n";
    return;
  }

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

  std::list<GlobalPosition> globalPositions;
  std::vector<RelevanceData>::const_iterator r_cur = relevanceData.begin();

  // transform two dimensional coordinates to 1 dimensional
  // and create blocks with relevant informations
  while(r_cur != relevanceData.end())
  {
    GlobalPosition fragm = transform2global(*r_cur, linePos);
    globalPositions.push_back(fragm);
    ++r_cur;
  }

  // compute blocks without relevance by using the current block and the next block with relevant values
  std::list<GlobalPosition>::iterator curBlock = globalPositions.begin();
  std::list<GlobalPosition>::iterator preBlock = globalPositions.begin();

  for(; curBlock != globalPositions.end(); ++curBlock)
  {
    GlobalPosition zero = diffFrom2RelevanceData(preBlock, curBlock);

    if(zero.length != 0)
      globalPositions.insert(curBlock, zero);

    preBlock = curBlock;
  }

  std::list<GlobalPosition>::iterator lastFrag = globalPositions.end();
  --lastFrag;

  // if the last block do not reach the end of the content, this will compute the last block
  if(lastFrag->begin + lastFrag->length < *(linePos.end()-1))
  {
    uint16_t endPos = lastFrag->begin + lastFrag->length;

    GlobalPosition lastZero;
    lastZero.length = *(linePos.end()-1) - endPos;
    lastZero.begin = endPos;
    lastZero.relevance = 0;

    globalPositions.push_back(lastZero);
  }

  // check if all datablocks have the correct size... otherwise we split this
  for(std::list<GlobalPosition>::iterator it = globalPositions.begin(); it != globalPositions.end(); ++it)
  {
    const std::size_t dbConstSize = C_LINE_BYTES + C_COLUMN_BYTES + DB_HEADER_LENGTH_BYTES + (usingTimestamp ? C_TIMESTAMP_BYTES : 0);
    const std::size_t maxTextSize = MAX_DB_LENGTH - dbConstSize;

    if( it->length > maxTextSize )
    {
      const std::size_t numParts = it->length/maxTextSize;
      const std::size_t lastPart = it->length % maxTextSize;

      for(unsigned int i = 0; i < numParts; ++i)
      {
        GlobalPosition tmp;
        tmp.relevance = it->relevance;
        tmp.length = maxTextSize;
        tmp.begin = it->begin + maxTextSize*i;

        globalPositions.insert(it, tmp);
      }

      if(lastPart != 0)
      {
        GlobalPosition tmp;
        tmp.relevance = it->relevance;
        tmp.length = lastPart;
        tmp.begin = it->begin + maxTextSize*numParts;

        globalPositions.insert(it, tmp);
      }
      std::list<GlobalPosition>::iterator tmp_it = it;
      ++it;
      globalPositions.erase(tmp_it);
    }
  }

  // create datablocks
  unsigned int sequNr = 0;
  for(std::list<GlobalPosition>::iterator it = globalPositions.begin(); it != globalPositions.end(); ++it)
  {
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
    text.text = content.substr(it->begin, it->length);
    RelevanceData rel_tmp = transform2localRelData(*it, linePos);
    text.line = rel_tmp.pos.y;
    text.column = rel_tmp.pos.x;

    ByteArray_sPtr content(new ByteArray);
    content->insert(text);
    db->addContent( content );
    db->setRelevanceData( rel_tmp );

    dbFifo->push(db);
  }
}

void SplitEncoding::partSensor(const DBDataObjectID& doid, const float& value, const bool& usingTimestamp)
{
  static unsigned int sNr = 0;

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
    if( int(gp.begin - len[i]) < 0 )
    {
      index = i-1;
      break;
    }
  }

  RelevanceData rel;
  rel.pos.len_x = gp.length;
  rel.pos.x = gp.begin - len[index];
  rel.pos.y = index;
  rel.relevanceValue = gp.relevance;

  return rel;
}

const SplitEncoding::GlobalPosition SplitEncoding::transform2global(const RelevanceData& r, const std::vector<std::size_t>& len)
{
  GlobalPosition gp;
  gp.length = r.pos.len_x;
  gp.begin = r.pos.x + len[r.pos.y];
  gp.relevance = r.relevanceValue;

  return gp;
}

// computes the global position between two blocks
const SplitEncoding::GlobalPosition SplitEncoding::diffFrom2RelevanceData(
    const std::list<GlobalPosition>::iterator& pre,
    const std::list<GlobalPosition>::iterator& cur)
{
  GlobalPosition gp;
  gp.begin = (cur == pre) ? 0 : pre->begin + pre->length;
  gp.length = (cur == pre) ? cur->begin : cur->begin - (pre->begin + pre->length);
  gp.relevance = 0;

  return gp;
}

std::ostream& operator<<(std::ostream& out, const SplitEncoding::GlobalPosition& gp)
{
  out << "pos: " << gp.begin
      << " length: " << gp.length
      << " relevance: " << gp.relevance;
  return out;
}
