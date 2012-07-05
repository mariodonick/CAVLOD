/*
 * @brief DataBlock<DATA>.h
 *
 */

#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include "../Tools/Bin.h"
#include "../Tools/ByteArray.h"
#include "Content.h"

#include <vector>
#include <iosfwd>
#include <iostream>

#include "DataBlockHeader.h"

template<class DATA>
class DataBlock
{
public:
  DataBlock();
  virtual ~DataBlock();

  DATA* getContent();

  const std::size_t contentSize();

  const DataBlockHeader& getHeader() const;
  void setHeader(const DataBlockHeader& dbh);

  const Bin<24>& getDataObjectID() const;
  const Bin<10>& getDataType() const;
  const HalfWord& getSequenceNumber() const;
  const Bin<6>& getConfig() const;
  const HalfWord& getLength() const;

  void setDataObjectID(const Bin<24>& doid);
  void setDataType(const Bin<10>& dt);
  void setSequenceNumber(const HalfWord& sn);
  void setConfig(const Bin<6>& conf);

  void addContent(DATA* content, const unsigned int& length);
  void deleteContent();
  const bool isContentEmpty() const;

  // return the pointer from the object at back and then delete this pointer from the vector
  DATA* back();

  void dump(std::ostream& out);

private:
  DataBlockHeader header;
  std::vector<DATA*> content;
};

template<class DATA>
class CompareDB
{
public:
  bool operator()(const DataBlock<DATA>* lhs, const DataBlock<DATA>* rhs) const
  {
    return lhs->getSequenceNumber() > rhs->getSequenceNumber();
  }
};




template<class DATA>
DataBlock<DATA>::DataBlock()
{
}

template<class DATA>
DataBlock<DATA>::~DataBlock()
{
//  std::cout << "datablock destructor size: " << content.size() << "\n";
  while( !content.empty() )
  {
//    std::cout << "datablock size: " << content.size() << "\n";
    DATA* data = content.back();
    content.pop_back();
    delete data;
  }
}

template<class DATA>
const DataBlockHeader& DataBlock<DATA>::getHeader() const
{
  return header;
}

template<class DATA>
void DataBlock<DATA>::setHeader(const DataBlockHeader& dbh)
{
  header = dbh;
}

template<class DATA>
const Bin<24>& DataBlock<DATA>::getDataObjectID() const
{
  return header.getDataObjectID();
}

template<class DATA>
const Bin<10>& DataBlock<DATA>::getDataType() const
{
  return header.getDataType();
}

template<class DATA>
const HalfWord& DataBlock<DATA>::getSequenceNumber() const
{
  return header.getSequenceNumber();
}

template<class DATA>
const Bin<6>& DataBlock<DATA>::getConfig() const
{
  return header.getConfig();
}

template<class DATA>
const HalfWord& DataBlock<DATA>::getLength() const
{
  return header.getLength();
}

template<class DATA>
void DataBlock<DATA>::setDataObjectID(const Bin<24>& doid)
{
  header.setDataObjectID(doid);
}

template<class DATA>
void DataBlock<DATA>::setDataType(const Bin<10>& dt)
{
  header.setDataType(dt);
}

template<class DATA>
void DataBlock<DATA>::setSequenceNumber(const HalfWord& sn)
{
  header.setSequenceNumber(sn);
}

template<class DATA>
void DataBlock<DATA>::setConfig(const Bin<6>& conf)
{
  header.setConfig(conf);
}

template<class DATA>
DATA* DataBlock<DATA>::back()
{
  DATA* data = content.back();
  content.pop_back();
  return data;
}

template<class DATA>
const std::size_t DataBlock<DATA>::contentSize()
{
  return header.getLength().to_uint() - DB_LENGTH_BYTES;
}

template<class DATA>
void DataBlock<DATA>::addContent(DATA* c, const unsigned int& len)
{
//  std::cout << "DB: len: " << len << "\n";

  unsigned int length = header.getLength().to_uint() + len;
  header.setLength(length);

//  std::cout << "DB: new len: " << header.getLength().to_uint() << "\n";

  content.push_back(c);

//  std::cout << "addcontent size: " << content.size() << "\n";
}

template<class DATA>
void DataBlock<DATA>::deleteContent()
{
  content.clear();
  header.length = 0;
}

template<class DATA>
DATA* DataBlock<DATA>::getContent()
{
  if(content.empty())
  {
    std::cerr << "Content is empty" << std::endl;
    throw;
  }

  DATA* tmp = content.back();
  content.pop_back();
  return tmp;
}

template<class DATA>
const bool DataBlock<DATA>::isContentEmpty() const
{
  return content.empty();
}

template<class DATA>
void DataBlock<DATA>::dump(std::ostream& out)
{
  header.dump(out);
  out << "Content: \n";
  typename std::vector<DATA*>::iterator it = content.begin();
  for(; it != content.end(); ++it )
      out << *(*it) << "\n";
}
#endif /* DATABLOCK_H_ */
