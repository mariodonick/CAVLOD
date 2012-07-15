/*
 * @brief UniversalDecoder.h
 *
 */

#ifndef UNIVERSALDECODER_H_
#define UNIVERSALDECODER_H_

#include "Decoder.h"
#include "../DataManagement/DataBlock.h"

#include <map>
#include <vector>
#include <iostream>

template<class T>
class UniversalDecoder : public Decoder<T>
{

  typedef typename std::map<DBDataObjectID, std::map<DBSequenceNumber, T> > TwoDimMap;

public:
  UniversalDecoder();
  virtual ~UniversalDecoder();

protected:
  void decode(const DBDataObjectID& doid, const DBSequenceNumber& seqNum, T obj);

protected:
  std::vector<T> sortedContent;

private:
  unsigned int old_line;
  TwoDimMap decodedData;
};



template<class T>
UniversalDecoder<T>::UniversalDecoder()
: old_line(0)
{

}

template<class T>
UniversalDecoder<T>::~UniversalDecoder()
{
  sortedContent.clear();

//  std::cout << "erase twodim map!\n";
  typename TwoDimMap::iterator outerMap_it = decodedData.begin();
//  std::cout << "delete doid key: " << outerMap_it->first << "\n";
  for( ; outerMap_it != decodedData.end(); ++outerMap_it )
  {
    typename std::map<DBSequenceNumber, T>::iterator innerMap_it = outerMap_it->second.begin();
    for(; innerMap_it != outerMap_it->second.end(); ++innerMap_it )
    {
      const T tmp = innerMap_it->second;
//      std::cout << "delete sequenceNr key: " << innerMap_it->first << "\n";
      outerMap_it->second.erase(innerMap_it);
    }
  }
//  std::cout << "destructor UniversalDecoder end\n";
}

template<class T>
void UniversalDecoder<T>::decode(const DBDataObjectID&doid, const DBSequenceNumber& seqNr, T obj)
{
  typename TwoDimMap::iterator tmp_it = decodedData.find(doid);

  if( tmp_it == decodedData.end() )
    decodedData[doid].insert( std::make_pair(seqNr, obj) );
  else
    tmp_it->second.insert( std::make_pair(seqNr, obj) );

  sortedContent.clear();

  typename TwoDimMap::iterator outerMap_it = decodedData.begin();
  for( ; outerMap_it != decodedData.end(); ++outerMap_it )
  {
    typename std::map<DBSequenceNumber, T>::iterator innerMap_it = outerMap_it->second.begin();
    for(; innerMap_it != outerMap_it->second.end(); ++innerMap_it )
    {
      std::cout << "DOID_KEY: " << outerMap_it->first.to_uint() << " SEQ_KEY: " << innerMap_it->first.to_uint() << " VALUE: " << *innerMap_it->second << "\n";
      sortedContent.push_back(innerMap_it->second);
    }
  }
}

#endif /* UNIVERSALDECODER_H_ */
