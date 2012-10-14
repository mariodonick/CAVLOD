/**
 * @brief Bin.h
 */

#ifndef BIN_H_
#define BIN_H_

#include <bitset>
#include <iostream> // todo unschön wegen 1 cerr :(

const unsigned int BIT_PER_BYTE = 8;
const unsigned int RSHIFT_TO_BYTE = 3;

template<unsigned int BAND_WIDTH>
class Bin
{
public:
  Bin() : number(0u){}
  Bin(const unsigned long& v) : number(v){}
  Bin(const std::string& s) : number(s){}
  Bin(const std::bitset<BAND_WIDTH>& bs) : number(bs){}
  Bin(const Bin<BAND_WIDTH>& bin) : number(bin.to_ulong()){}
  virtual ~Bin(){}

  const bool operator[](const std::size_t& pos) const
  {
    return number[pos];
  }

  typename std::bitset<BAND_WIDTH>::reference operator[](const std::size_t& pos)
  {
    return number[pos];
  }

  void reset()
  {
    number.reset();
  }

  void set(const std::size_t& pos, const bool& value = true)
  {
    number.set(pos, value);
  }

  // toggle all bits
  void flip()
  {
    number.flip();
  }

  // flip one bit at position pos
  void flip(const std::size_t& pos)
  {
    number.flip(pos);
  }

  // count all bits with value one
  const std::size_t count() const
  {
    return number.count();
  }

  // return true if more than 0 bits are set (dec number is greater than 0)
  const std::size_t any() const
  {
    return number.any();
  }

  // return the length (band width) of the binary number
  const std::size_t size() const
  {
    return number.size();
  }

  // return true if no bit is set
  const bool none() const
  {
    return number.none();
  }

  //cut the binary value and return the piece
  template<unsigned int FIRST_BIT, unsigned int LAST_BIT>
  Bin<LAST_BIT-FIRST_BIT> separate() const
  {
    Bin<LAST_BIT-FIRST_BIT> tmp;
    unsigned int index = 0;
    for(unsigned int i = FIRST_BIT; i < LAST_BIT; ++i)
    {
      tmp[index] = number[i];
      index++;
    }
    return tmp;
  }

  //return the value of the bit at position pos
  const bool test(const std::size_t& pos) const
  {
    return number.test(pos);
  }

  Bin<BAND_WIDTH>& operator&= (const Bin<BAND_WIDTH>& rhs)
  {
    number &= std::bitset<BAND_WIDTH>(rhs.to_ulong());
    return *this;
  }

  Bin<BAND_WIDTH>& operator|= (const Bin<BAND_WIDTH>& rhs)
  {
    number |= std::bitset<BAND_WIDTH>(rhs.to_ulong());
    return *this;
  }

  Bin<BAND_WIDTH>& operator^= (const Bin<BAND_WIDTH>& rhs)
  {
    number ^= std::bitset<BAND_WIDTH>(rhs.to_ulong());
    return *this;
  }

  Bin<BAND_WIDTH> operator&(const Bin<BAND_WIDTH>& rhs)
  {
    return Bin<BAND_WIDTH>(number.to_ulong() & rhs.to_ulong());
  }

  Bin<BAND_WIDTH> operator&(const unsigned int& rhs)
  {
    return Bin<BAND_WIDTH>(number & rhs);
  }

  Bin<BAND_WIDTH> operator|(const Bin<BAND_WIDTH>& rhs)
  {
    return Bin<BAND_WIDTH>(number.to_ulong() | rhs.to_ulong());
  }

  Bin<BAND_WIDTH> operator|(const unsigned int& rhs)
  {
    return Bin<BAND_WIDTH>(number | rhs);
  }

  Bin<BAND_WIDTH> operator^(const Bin<BAND_WIDTH>& rhs)
  {
    return Bin<BAND_WIDTH>(number.to_ulong() ^ rhs.to_ulong());
  }

  Bin<BAND_WIDTH> operator^(const unsigned int& rhs)
  {
    return Bin<BAND_WIDTH>(number ^ rhs);
  }

  Bin<BAND_WIDTH>& operator<<= (const std::size_t& pos)
  {
    number <<= pos;
    return *this;
  }

  Bin<BAND_WIDTH>& operator>>= (const std::size_t& pos)
  {
    number >>= pos;
    return *this;
  }

  Bin<BAND_WIDTH> operator~() const
  {
    Bin<BAND_WIDTH> tmp(number);
    tmp.flip();
    return tmp;
  }

  Bin<BAND_WIDTH> operator<<(const std::size_t& pos) const
  {
    std::bitset<BAND_WIDTH> tmp(number);
    tmp <<= pos;
    return Bin<BAND_WIDTH>(tmp);
  }

  Bin<BAND_WIDTH> operator>>(const std::size_t& pos) const
  {
    std::bitset<BAND_WIDTH> tmp(number);
    tmp >>= pos;
    return Bin<BAND_WIDTH>(tmp);
  }

  bool operator== (const Bin<BAND_WIDTH>& rhs) const
  {
    return number == rhs.to_ulong();
  }

  bool operator!= (const Bin<BAND_WIDTH>& rhs) const
  {
    return number != rhs.to_ulong();
  }

  unsigned long to_ulong() const
  {
    if(size() > 64)
    {
      std::cerr << "Tthe binary is bigger than 64Bit we return 0\n";
      return 0;
    }
    return number.to_ulong();
  }

  std::string to_string() const
  {
    return number.to_string();
  }

  unsigned int to_uint() const
  {
    return static_cast<unsigned int>( number.to_ulong() );
  }

  Bin<BAND_WIDTH> operator+(const Bin<BAND_WIDTH>& value) const
  {
    return Bin<BAND_WIDTH>(this->to_ulong() + value.to_ulong());
  }

  Bin<BAND_WIDTH> operator+(const unsigned long& value) const
  {
    return Bin<BAND_WIDTH>(this->to_ulong() + value);
  }

  Bin<BAND_WIDTH> operator-(const Bin<BAND_WIDTH>& value) const
  {
    return Bin<BAND_WIDTH>(this->to_ulong() - value.to_ulong());
  }

  Bin<BAND_WIDTH> operator-(const unsigned long& value) const
  {
    return Bin<BAND_WIDTH>(this->to_ulong() - value);
  }

  Bin<BAND_WIDTH> operator*(const Bin<BAND_WIDTH>& value) const
  {
    return Bin<BAND_WIDTH>(this->to_ulong() * value.to_ulong());
  }

  Bin<BAND_WIDTH> operator*(const unsigned long& value) const
  {
    return Bin<BAND_WIDTH>(this->to_ulong() * value);
  }

  Bin<BAND_WIDTH> operator/(const Bin<BAND_WIDTH>& value) const
  {
    if(value == 0) throw("division to zero");
    return Bin<BAND_WIDTH>(this->to_ulong() / value.to_ulong());
  }

  Bin<BAND_WIDTH> operator/(const unsigned long& value) const
  {
    if(value == 0) throw("division to zero");
    return Bin<BAND_WIDTH>(this->to_ulong() / value);
  }

  Bin<BAND_WIDTH>& operator+=(const Bin<BAND_WIDTH>& value)
  {
    number = number.to_ulong() + value.to_ulong();
    return *this;
  }

  Bin<BAND_WIDTH>& operator+=(const unsigned long& value)
  {
    number = number.to_ulong() + value;
    return *this;
  }

  Bin<BAND_WIDTH>& operator-=(const Bin<BAND_WIDTH>& value)
  {
    number = number.to_ulong() - value.to_ulong();
    return *this;
  }

  Bin<BAND_WIDTH>& operator-=(const unsigned long& value)
  {
    number = number.to_long() - value;
    return *this;
  }

  Bin<BAND_WIDTH>& operator*=(const Bin<BAND_WIDTH>& value)
  {
    number = number.to_ulong() * value.to_ulong();
    return *this;
  }

  Bin<BAND_WIDTH>& operator*=(const unsigned long& value)
  {
    number = number.to_ulong() * value;
    return *this;
  }

  Bin<BAND_WIDTH>& operator/=(const Bin<BAND_WIDTH>& value)
  {
    if(value == 0) throw("division to zero");
    number = number.to_ulong() / value.to_ulong();
    return *this;
  }

  Bin<BAND_WIDTH>& operator/=(const unsigned long& value)
  {
    if(value == 0) throw("division to zero");
    number = number.to_ulong() / value;
    return *this;
  }

  Bin<BAND_WIDTH>& operator=(const Bin<BAND_WIDTH>& rhs)
  {
    number = rhs.to_ulong();
    return *this;
  }

  Bin<BAND_WIDTH>& operator=(const unsigned long& rhs)
  {
    number = rhs;
    return *this;
  }

  Bin<BAND_WIDTH>& operator=(const std::string& rhs)
  {
    number = rhs;
    return *this;
  }

  Bin<BAND_WIDTH>& operator=(const std::bitset<BAND_WIDTH>& rhs)
  {
    number = rhs;
    return *this;
  }

  const bool operator>(const Bin<BAND_WIDTH>& rhs) const
  {
    return number.to_ulong() > rhs.to_ulong();
  }

  const bool operator<(const Bin<BAND_WIDTH>& rhs) const
  {
    return number.to_ulong() < rhs.to_ulong();
  }

  const bool operator>=(const Bin<BAND_WIDTH>& rhs) const
  {
    return number.to_ulong() >= rhs.to_ulong();
  }

  const bool operator<=(const Bin<BAND_WIDTH>& rhs) const
  {
    return number.to_ulong() <= rhs.to_ulong();
  }

  friend const bool operator<=(const Bin<BAND_WIDTH>& lhs, const unsigned int& rhs)
  {
    return lhs.to_uint() <= rhs;
  }

  std::ostream& dumpBin(std::ostream& os, Bin<BAND_WIDTH>& rhs)
  {
    return os << rhs.to_string() << "\n";
  }

  friend std::ostream& operator<<(std::ostream& os, Bin<BAND_WIDTH>& rhs)
  {
    for(unsigned int i = 0; i < BAND_WIDTH; ++i)
      os << rhs[i];

    return os;
  }

private:
  std::bitset<BAND_WIDTH> number;
};


typedef Bin<8ul> Byte;
typedef Bin<16ul> HalfWord;
typedef Bin<32ul> Word;
typedef Bin<64ul> QuadWord;

template<unsigned int H, unsigned int L>
inline Bin<L+H> merge(const Bin<L>& lsb, const Bin<H>& msb)
{
  Bin<L+H> tmp;

  for(unsigned int i = 0; i < L; ++i)
    tmp[i] = lsb[i];

  for(unsigned int i = 0; i < H; ++i)
    tmp[L+i] = msb[i];
  return tmp;
}

template<unsigned int FIRST, unsigned int SECOND, unsigned int THIRD, unsigned int FOURTH>
inline Bin<FIRST+SECOND+THIRD+FOURTH> mergeFour(const Bin<FIRST>& bits0, const Bin<SECOND>& bits1,
                                                const Bin<THIRD>& bits2, const Bin<FOURTH>& bits3)
{
  Bin<FIRST+SECOND> tmp0 = merge(bits0, bits1);
  Bin<THIRD+FOURTH> tmp1 = merge(bits2, bits3);
  Bin<FIRST+SECOND+THIRD+FOURTH> result = merge(tmp0, tmp1);

  return result;
}

template<unsigned int BIT_LENGTH>
inline Bin<BIT_LENGTH> char2Bin(const char* data)
{
  Bin<BIT_LENGTH> tmp;
  for(unsigned int i = 0; i < (BIT_LENGTH >> RSHIFT_TO_BYTE); ++i)
    for(unsigned int bit_pos = 0; bit_pos < 8; ++bit_pos)
      tmp[i * BIT_PER_BYTE + bit_pos] = Byte(data[i])[bit_pos];

  return tmp;
}

inline unsigned int char2uint(const char* data, const std::size_t& num_bytes)
{
  if(num_bytes > 4){ /*std::cerr << "ERROR: array is to big for one unsigned char\n";*/ throw; } // todo richtige exception
  unsigned int tmp = 0;
  for(unsigned int i = 0; i < num_bytes; ++i)
  {
    unsigned int shift = (i==0)?0:8;
    tmp = (tmp << shift) | (data[num_bytes-1-i]  & 0xFF);
  }
  return tmp;
}

#endif /* BIN_H_ */
