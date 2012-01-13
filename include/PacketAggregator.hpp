#ifndef IPACKETAGGREGATOR_H_
# define IPACKETAGGREGATOR_H_

#include <queue>
#include <iostream>
#include <string>
#include "ProtocolPacket.h"

class	PacketAggregator
{
public:
  PacketAggregator(void);
  ~PacketAggregator(void);
  PacketAggregator(const PacketAggregator&);
  PacketAggregator&	operator=(const PacketAggregator&);

  bool concat(char *str, int size);
  int  aggregatePacketToChar(void);
  int  aggregateCharToPacket(void);
  int  aggregateCharToPackets(void);
  bool empty(void);
  ProtocolPacket *front(void);
  bool pop(void);
  bool push(ProtocolPacket *);
  bool erase(void);
  unsigned int getSize(void)const;
  unsigned int getPacketSize(void)const;
  char *getMsg(void)const;
private:
  std::queue<ProtocolPacket *>	_packetQueue;
  char				_buffer[4096];
  unsigned int			_index;
};

#endif	// IPACKETAGGREGATOR_H_
