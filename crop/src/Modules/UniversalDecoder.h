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


template<class T>
class UniversalDecoder : public Decoder<T>
{

  typedef typename std::map<Doid, std::map<SequenceNum, T*> > TwoDimMap;

public:
  UniversalDecoder();
  virtual ~UniversalDecoder();

protected:
  void decode(const Doid& doid, const SequenceNum& seqNum, T* obj);

protected:
  std::vector<T*> sortedContent;

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
    typename std::map<SequenceNum, T*>::iterator innerMap_it = outerMap_it->second.begin();
    for(; innerMap_it != outerMap_it->second.end(); ++innerMap_it )
    {
      const T* tmp = innerMap_it->second;
//      std::cout << "delete sequenceNr key: " << innerMap_it->first << "\n";
      outerMap_it->second.erase(innerMap_it);
      delete tmp;
    }
  }
//  std::cout << "destructor UniversalDecoder end\n";
}

template<class T>
void UniversalDecoder<T>::decode(const Doid&doid, const SequenceNum& seqNr, T* obj)
{
  typename TwoDimMap::iterator tmp_it = decodedData.find(doid);

//  std::cout << "decode: " << doid << " seqnr: " << seqNr << "\n";

  if( tmp_it == decodedData.end() )
  {
//    std::cout << "doid not found insert\n";
    decodedData[doid].insert( std::make_pair(seqNr, obj) );
  }
  else
  {
//    std::cout << "doid found insert\n";
    tmp_it->second.insert( std::make_pair(seqNr, obj) );
  }

  sortedContent.clear();
//  std::cout << "content after clear size: " << sortedContent.size() << "\n";

  typename TwoDimMap::iterator outerMap_it = decodedData.begin();
  for( ; outerMap_it != decodedData.end(); ++outerMap_it )
  {
    typename std::map<SequenceNum, T*>::iterator innerMap_it = outerMap_it->second.begin();
    for(; innerMap_it != outerMap_it->second.end(); ++innerMap_it )
    {
      std::cout << "DOID_KEY: " << outerMap_it->first << " SEQ_KEY: " << innerMap_it->first << " VALUE: " << *innerMap_it->second << "\n";
      sortedContent.push_back(innerMap_it->second);
//      std::cout << "content size: " << sortedContent.size() << "\n";
    }
  }

//  std::cout << "display vector\n";
//  typename std::vector<T*>::const_iterator it = sortedContent.begin();
//   for(; it != sortedContent.end(); ++it)
//   {
//     std::cout << *(*it) << " ";
//   }

}

#endif /* UNIVERSALDECODER_H_ */
