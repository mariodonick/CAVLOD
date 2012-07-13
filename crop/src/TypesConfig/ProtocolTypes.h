/*
 * @brief ProtocolTypes.h
 *
 */

#ifndef PROTOCOLTYPES_H_
#define PROTOCOLTYPES_H_

template<unsigned int N>
class Bin;

typedef Bin<4> MsgVersion;
typedef Bin<128> MsgSrcAddress;
typedef Bin<128> MsgDstAddress;
typedef Bin<32> MsgCrc32;
typedef Bin<16> MsgCrc16;
typedef Bin<12> MsgConfig;
typedef Bin<24> MsgLength;

typedef Bin<10> DBDatatype;
typedef Bin<6> DBConfig;
typedef Bin<16> DBSequenceNumber;
typedef Bin<24> DBDataObjectID;
typedef Bin<16> DBLength;

enum MsgAddressType
{
  IP_V6 = 0
};

enum EMsgVersion
{
  VERSION_1 = 1,
//  VERSIONT_2,

};

#endif /* PROTOCOLTYPES_H_ */
