
#include		<string.h>
#include		<cstdlib>
#include		"PacketFactory.hpp"

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

ProtocolPacket *		PacketFactory::createPacket()
{
  ProtocolPacket * packet = new ProtocolPacket;
  packet->header.magic = PACKET_MAGIC;
  packet->header.size = 0;
  packet->header.group = 0;
  packet->header.instruction = 0;
  packet->data = NULL;
  return (packet);
}

ProtocolPacket *		PacketFactory::createPacket(eProtocolPacketGroup group, ushort instruction,
							    DataRawType const * data, ushort size)
{
  ProtocolPacket * packet = PacketFactory::createPacket();
  if (!packet)
    return (NULL);
  packet->header.size = size;
  packet->header.group = group;
  packet->header.instruction = instruction;
  packet->data = data;
  return (packet);
}

ProtocolPacket *		PacketFactory::createPacket(eProtocolPacketGroup group,
							    ushort instruction,
							    PacketData & data)
{
  return (PacketFactory::createPacket(group, instruction, data.getData(), data.getDataSize()));
}

ProtocolPacket *		PacketFactory::createPacket(eProtocolPacketGroup group,
							    ushort instruction,
							    PacketData * data)
{
  return (PacketFactory::createPacket(group, instruction, data->getData(), data->getDataSize()));
}

eProtocolPacketGroup			PacketFactory::getPacketGroup(ProtocolPacket * packet)
{
  return (packet && packet->header.group < GROUP_MAX ?
	   static_cast<eProtocolPacketGroup>(packet->header.group)
  	  : GROUP_ERROR);
}

ushort				PacketFactory::getPacketInstruction(ProtocolPacket * packet)
{
  return (packet ? packet->header.instruction : 0);
}

PacketData *		PacketFactory::getPacketData(ProtocolPacket * packet)
{
  if (!packet)
    return (NULL);
  return (new PacketData(packet->data, packet->header.size));
}

ushort				PacketFactory::getPacketDataSize(ProtocolPacket * packet)
{
  return (packet ? packet->header.size : 0);
}

void				PacketFactory::destroyPacket(ProtocolPacket * packet)
{
  // free(const_cast<char *>(packet->data));
  free(packet);
}
