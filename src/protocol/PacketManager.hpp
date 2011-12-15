
#ifndef			PACKETMANAGER_H_
# define		PACKETMANAGER_H_

# include		<map>
# include		"PacketFactory.hpp"
# include		"ProtocolPacketData.hpp"
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
 // public:
 //  bool				send(UserNetwork & net, eGroupType group,
 // 				     ushort instruction, char const * data, uint size);
 //  bool				send(UserNetwork & net, eGroupType group,
 // 				     ushort instruction, ProtocolPacketData & data);
 //  bool				send(UserNetwork & net, eGroupType group,
 // 				     ushort instruction, std::string const &);

 //  bool				rcsv(UserNetwork * socket);
 //  bool				rcsv(User * user);

 // public:
 //  void				DeleteSocket(UserNetwork * net, User * user);

/* ************************************************************************* */
/*                             Private Functions                             */
/* ************************************************************************* */
 // private:
 //  void				actionError();
 //  ProtocolPacket *		RcvPacket(UserNetwork * net,
 // 					  User * user = NULL);
};

#endif				// !PACKETMANAGER_H_

