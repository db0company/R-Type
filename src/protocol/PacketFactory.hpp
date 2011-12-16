
#ifndef				PACKETFACTORY_H_
# define			PACKETFACTORY_H_

# include			<string>
# include			"PacketData.hpp"
# include			"ProtocolPacket.h"
# include			"eProtocolPacketGroup.h"

class				PacketFactory
{
/* ************************************************************************* */
/*                             Private coplien form                          */
/* ************************************************************************* */
 private:
  PacketFactory(void) {};
  PacketFactory(PacketFactory const &) {};
  PacketFactory &		operator=(PacketFactory const &) { return (*this); };
  ~PacketFactory(void) {};

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  static ProtocolPacket *	createPacket(void);
  static ProtocolPacket *	createPacket(eProtocolPacketGroup group, ushort instruction,
					     DataRawType const * data, ushort size);
  static ProtocolPacket *	createPacket(eProtocolPacketGroup group, ushort instruction,
					     PacketData & data);
  static eProtocolPacketGroup	getPacketGroup(ProtocolPacket * packet);
  static ushort			getPacketInstruction(ProtocolPacket * packet);
  static PacketData *	getPacketData(ProtocolPacket * packet);
  static ushort			getPacketDataSize(ProtocolPacket * packet);
  static void			destroyPacket(ProtocolPacket * packet);
};

#endif				// !PACKETFACTORY_H_

