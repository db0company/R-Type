#ifndef 	PACKETMANAGER_H_
# define	PACKETMANAGER_H_

# include	<map>
# include	"PacketFactory.hpp"
# include	"PacketData.hpp"
# include	"IProtocolAction.hpp"

class User;
class Server;
class		PacketManager
{
 private:
  std::map<eProtocolPacketGroup, IProtocolAction *>	groupaction;

 public:
  PacketManager(void);
  PacketManager(PacketManager const &);
  PacketManager &		operator=(PacketManager const &);
  ~PacketManager(void);

 public:
  bool				Process(ProtocolPacket *packet, User *user, Server&);
  void				actionError();
  // ProtocolPacket *		RcvPacket(User * user, bool);
};

#endif				// !PACKETMANAGER_H_

