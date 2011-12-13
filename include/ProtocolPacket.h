
#ifndef			PROTOCOLPACKET_H_
# define		PROTOCOLPACKET_H_

# include		"types.h"

# define		PACKET_MAGIC	97463

struct			ProtocolPacketHeader
{
  ushort		magic;
  ushort		size;
  ushort		type;
};

struct			ProtocolPacket
{
  ProtocolPacketHeader	header;
  DataRawType *		data;
};

#endif			// !PROTOCOLPACKET_H_
