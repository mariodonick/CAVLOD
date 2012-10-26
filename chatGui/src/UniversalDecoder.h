/*
 * @brief UniversalDecoder.h
 *
 */

#ifndef UNIVERSALDECODER_H_
#define UNIVERSALDECODER_H_

#include <map>
#include <vector>

template<class T>
class UniversalDecoder
{

  typedef typename std::map<uint, std::map<uint, T> > StdMap2D;
  typedef typename std::map<uint, T> StdMap1D;

public:
  typedef typename std::vector<std::vector<T> > StdVec2D;
  typedef typename std::vector<T> StdVec1D;

public:
  UniversalDecoder();
  virtual ~UniversalDecoder();

  void decode(const uint& doid, const uint& seqNum, T obj);
  const StdVec2D& getSortedContent() const;
  void dump(std::ostream& out) const;

private:
  void clear();

private:
  StdMap2D decodedData;
  StdVec2D sortedContent;
};



template<class T>
UniversalDecoder<T>::UniversalDecoder()
{

}

template<class T>
UniversalDecoder<T>::~UniversalDecoder()
{
  clear();

  typename StdMap2D::iterator outerMap_it = decodedData.begin();

  for( ; outerMap_it != decodedData.end(); ++outerMap_it )
  {
    typename StdMap1D::iterator innerMap_it = outerMap_it->second.begin();
    for(; innerMap_it != outerMap_it->second.end(); ++innerMap_it )
    {
      outerMap_it->second.erase(innerMap_it);
    }
  }
}

template<class T>
void UniversalDecoder<T>::decode(const uint& doid,
                                 const uint& seqNr,
                                 T obj)
{
  typename StdMap2D::iterator tmp_it = decodedData.find(doid);

  if( tmp_it == decodedData.end() )
    decodedData[doid].insert( std::make_pair(seqNr, obj) );
  else
    tmp_it->second.insert( std::make_pair(seqNr, obj) );

  clear();

  // fill sorted content - this should you implement more effective
  typename StdMap2D::iterator outerMap_it = decodedData.begin();
  for( ; outerMap_it != decodedData.end(); ++outerMap_it )
  {
    StdVec1D vecTmp;
    typename StdMap1D::iterator innerMap_it = outerMap_it->second.begin();
    for(; innerMap_it != outerMap_it->second.end(); ++innerMap_it )
    {
      vecTmp.push_back(innerMap_it->second);

    }
    sortedContent.push_back(vecTmp);
  }
}

template<class T>
const typename UniversalDecoder<T>::StdVec2D& UniversalDecoder<T>::getSortedContent() const
{
  return sortedContent;
}

template<class T>
void UniversalDecoder<T>::dump(std::ostream& out) const
{
  typename StdVec2D::const_iterator outer = sortedContent.begin();
  for(; outer != sortedContent.end(); ++outer)
  {
    typename StdVec1D::const_iterator inner = outer->begin();
    for(;inner != outer->end(); ++inner)
    {
      out << "" << *inner;
    }
    out << "\n";
  }
}

template<class T>
void UniversalDecoder<T>::clear()
{
  typename StdVec2D::iterator outer = sortedContent.begin();
  for(; outer != sortedContent.end(); ++outer)
    outer->clear();

  sortedContent.clear();
}

#endif /* UNIVERSALDECODER_H_ */
