
#ifndef			PACKETMANAGER_H_
# define		PACKETMANAGER_H_

# include		<map>
# include		"user/User.hpp"
# include		"PacketFactory.hpp"
# include		"PacketData.hpp"
# include		"iProtocolAction.hpp"

class			PacketManager
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  std::map<eProtocolPacketGroup, iProtocolAction *>	groupaction;

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */
 public:
  PacketManager(void);
  PacketManager(PacketManager const &);
  PacketManager &		operator=(PacketManager const &);
  ~PacketManager(void);

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  bool				send(User * user, eProtocolPacketGroup group,
 				     ushort instruction,
				     PacketData & data,
				     bool udp = false);
  bool				rcsv(User * user, bool udp = false);
  bool				Process(ProtocolPacket *packet, User *user);
/* ************************************************************************* */
/*                             Private Functions                             */
/* ************************************************************************* */
 // private:
  void				actionError();
  ProtocolPacket *		RcvPacket(User * user, bool);
};

#endif				// !PACKETMANAGER_H_

