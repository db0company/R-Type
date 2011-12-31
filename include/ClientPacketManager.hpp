#ifndef 	CLIENTPACKETMANAGER_H_
# define	CLIENTPACKETMANAGER_H_

# include	<map>
# include	"PacketFactory.hpp"
# include	"PacketData.hpp"
# include	"IClientProtocolAction.hpp"

class Client;
class		ClientPacketManager
{
 private:
  std::map<eProtocolPacketGroup, IClientProtocolAction *>	groupaction;

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
