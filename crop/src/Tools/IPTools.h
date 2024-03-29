/*
 * @brief IPTools.h
 *
 */

#ifndef IPTOOLS_H_
#define IPTOOLS_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <iostream>

#include "ByteArray.h"

typedef Bin<32> IPv4;
typedef Bin<128> IPv6;

inline bool readCurrentIP(std::string& ownIP, const char* interface)
{
  int sock_fd = socket( AF_INET , SOCK_DGRAM , 0 );
  if( sock_fd == -1 )
  {
    perror("socket");
    std::cerr << "Error: creating socket." << "\n";
    return false;
  }

  struct ifreq ifr;
  strcpy( ifr.ifr_name , interface );
  if( ioctl( sock_fd , SIOCGIFADDR , &ifr ) == -1 )
  {
    perror ("ioctl");
    std::cerr << "problems with ioctl."<< "\n";
    return false;
  }

  char* addr = inet_ntoa( ((struct sockaddr_in *) (&ifr.ifr_addr))->sin_addr );
  std::cout << "found your current ip - "<< interface << ": " << addr << "\n";

  close( sock_fd );
  ownIP = addr;
  return true;
}

inline const std::string ownIP()
{
  std::cout << "searching your own ip..."<< "\n";

  std::string ip;
  if( !readCurrentIP(ip, "eth0") )
    if( !readCurrentIP(ip, "wlan0") )
      if( !readCurrentIP(ip, "lxcbr0") )
        if( !readCurrentIP(ip, "lo") )
          ip = "127.0.0.1";
  return ip;
}

inline IPv4 ipv4StringToBin(const std::string& addr)
{
  uint32_t tmp;
  inet_pton(AF_INET, addr.c_str(), &tmp);
  return IPv4(tmp);
}

inline const std::string ipv4BinToString(const IPv4& addr)
{
  uint32_t tmp = addr.to_ulong();
  char str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &tmp, str, INET_ADDRSTRLEN);
  return std::string(str);
}

inline IPv6 ipv6StringToBin(const std::string& addr)
{
  struct sockaddr_in6 sa;
  inet_pton(AF_INET6, addr.c_str(), &sa.sin6_addr);

  //conversion to 128bit
  Bin<32> tmp0 = sa.sin6_addr.__in6_u.__u6_addr32[0];
  Bin<32> tmp1 = sa.sin6_addr.__in6_u.__u6_addr32[1];
  Bin<32> tmp2 = sa.sin6_addr.__in6_u.__u6_addr32[2];
  Bin<32> tmp3 = sa.sin6_addr.__in6_u.__u6_addr32[3];

  return mergeFour(tmp0, tmp1, tmp2, tmp3);
}

inline const std::string ipv6BinToString(const IPv6& addr)
{
  ByteArray ba;
  ba.insert(addr);

  char str[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, ba.dataPtr(), str, INET6_ADDRSTRLEN);
  return std::string(str);
}

#endif /* IPTOOLS_H_ */
