
#ifndef			PROTOCOLPACKET_H_
# define		PROTOCOLPACKET_H_

# include		"types.h"

# define		PACKET_MAGIC	9743

struct			ProtocolPacketHeader
{
  ushort		magic;
  ushort		size;
  ushort		group;
  ushort		instruction;
};

struct			ProtocolPacket
{
  ProtocolPacketHeader	header;
  DataRawType const *	data;
};

#endif			// !PROTOCOLPACKET_H_
