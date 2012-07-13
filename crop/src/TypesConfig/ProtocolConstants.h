/*
 * @brief ProtocolConstants.h
 *
 */

#ifndef PROTOCOLCONSTANTS_H_
#define PROTOCOLCONSTANTS_H_

//length
// message bytes
const std::size_t MSG_VER_CONFIG_LENGTH_BYTES = 2;
const std::size_t MSG_LENGTH_BYTES = 3;
const std::size_t MSG_CRC_16_BYTES = 2;
const std::size_t MSG_CRC_32_BYTES = 4;
const std::size_t MSG_ADDRESS_TYPE_IPV6_BYTES = 16;

// datablock bytes
const std::size_t DB_CONFIG_BITS = 6;
const std::size_t DB_DATA_TYPE_BITS = 10;
const std::size_t DB_DATA_TYPE_CONFIG_BYTES = (DB_CONFIG_BITS + DB_DATA_TYPE_BITS) >> 3;
const std::size_t DB_DATA_OBJECT_ID_BYTES = 3;
const std::size_t DB_SEQUENCE_NUMBER_BYTES = 2;
const std::size_t DB_LENGTH_BYTES = 2;

// content
const std::size_t C_TIMESTAMP_BYTES = 8;
// content text
const std::size_t C_LINE_BYTES = 2;
const std::size_t C_COLUMN_BYTES = 2;
//content Sensor
const std::size_t C_VALUE_BYTES = 4;

//header length
const std::size_t MSG_FIXED_HEADER_LENGTH_BYTES = MSG_VER_CONFIG_LENGTH_BYTES + MSG_LENGTH_BYTES;
const std::size_t DB_HEADER_LENGTH_BYTES = DB_DATA_TYPE_CONFIG_BYTES + DB_DATA_OBJECT_ID_BYTES + DB_SEQUENCE_NUMBER_BYTES + DB_LENGTH_BYTES;


#endif /* PROTOCOLCONSTANTS_H_ */
