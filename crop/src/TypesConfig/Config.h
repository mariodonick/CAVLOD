/*
 * @brief Config.h
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// general
const unsigned int SLEEP_MSECONDS_PACKETIZER = 2000; // allle bei 1000
const unsigned int SLEEP_MSECONDS_INPUT_SENSOR = 1000;
const unsigned int SLEEP_MSECONDS_INPUT_TEXT = 1000;

const unsigned int PORT = 5657;
const char* const IP_ADDRESS = "localhost";


// network
const size_t NETWORK_BUFFER_SIZE = 2*1024*1024;

#endif /* CONFIG_H_ */
