#ifndef 	CLIENTPACKETMANAGER_H_
# define	CLIENTPACKETMANAGER_H_

# include	<map>
# include	"PacketFactory.hpp"
# include	"PacketData.hpp"
# include	"iClientProtocolAction.hpp"
// # include	"Client.hpp"
class Client;
class		ClientPacketManager
{
 private:
  std::map<eProtocolPacketGroup, iClientProtocolAction *>	groupaction;

 public:
  ClientPacketManager(void);
  ClientPacketManager(ClientPacketManager const &);
  ClientPacketManager &		operator=(ClientPacketManager const &);
  ~ClientPacketManager(void);

 public:
  bool				Process(ProtocolPacket *, Client&);
  void				actionError();
};

#endif				// CLIENTPACKETMANAGER_H_
