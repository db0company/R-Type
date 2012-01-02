
#ifndef			PROTOCOLPACKET_H_
# define		PROTOCOLPACKET_H_

# include		"types.h"

# define		PACKET_MAGIC	9743
# include		<iostream>
# include		<cstring>
struct			ProtocolPacketHeader
{
  ushort		magic;
  ushort		size;
  ushort		group;
  ushort		instruction;
};

struct			ProtocolPacket
{
  ProtocolPacket()
  {
    memset(&(this->header), 0, sizeof(ProtocolPacketHeader));
    this->data = NULL;
  }
  ~ProtocolPacket(){}
  ProtocolPacket &operator=(ProtocolPacket const &other);
  ProtocolPacket(ProtocolPacket const &other)
  {
    this->header.magic = other.header.magic;
    this->header.size = other.header.size;
    this->header.group = other.header.group;
    this->header.instruction = other.header.instruction;
    memcpy(&(this->data), &(other.data), other.header.size);
  }
  ProtocolPacketHeader	header;
  DataRawType const *	data;
};

#endif			// !PROTOCOLPACKET_H_
