/*
 * @brief Config.h
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "Tools/Bin.h"

const unsigned int SLEEP_SECONDS = 1;
const unsigned int PORT = 5657;
const char* const IP_ADDRESS = "localhost";

//length
// message bytes
const unsigned int MSG_VER_CONFIG_LENGTH_BYTES = 2;
const unsigned int MSG_LENGTH_BYTES = 3;
const unsigned int MSG_CRC_16_BYTES = 2;
const unsigned int MSG_CRC_32_BYTES = 4;
const unsigned int MSG_ADDRESS_TYPE_IPV6_BYTES = 16;

// datablock bytes
const unsigned int DB_CONFIG_BITS = 6;
const unsigned int DB_DATA_TYPE_BITS = 10;
const unsigned int DB_DATA_TYPE_CONFIG_BYTES = (DB_CONFIG_BITS + DB_DATA_TYPE_BITS) >> RSHIFT_TO_BYTE;
const unsigned int DB_DATA_OBJECT_ID_BYTES = 3;
const unsigned int DB_SEQUENCE_NUMBER_BYTES = 2;
const unsigned int DB_LENGTH_BYTES = 2;

// content
const unsigned int C_TIMESTAMP_BYTES = 8;
// content text
const unsigned int C_LINE_BYTES = 2;
const unsigned int C_COLUMN_BYTES = 2;
//content Sensor
const unsigned int C_VALUE_BYTES = 4;

//header length
const unsigned int MSG_FIXED_HEADER_LENGTH_BYTES = MSG_VER_CONFIG_LENGTH_BYTES + MSG_LENGTH_BYTES;
const unsigned int DB_HEADER_LENGTH_BYTES = DB_DATA_TYPE_CONFIG_BYTES + DB_DATA_OBJECT_ID_BYTES + DB_SEQUENCE_NUMBER_BYTES + DB_LENGTH_BYTES;


// message
const Bin<128> SRC_ADDRESS = 127001;
const Bin<128> DST_ADDRESS = 19216823;
const Bin<12> MESSAGE_CONFIG = 0;
const HalfWord CRC_16 = 1;
const Word CRC_32 = 1;

// network
const unsigned int NETWORK_BUFFER_SIZE = 2*1024*1024;

#endif /* CONFIG_H_ */
