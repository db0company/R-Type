#ifndef PROTOCOLLOBBY_H_
# define PROTOCOLLOBBY_H_

# include	<map>
# include	"IProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketLobby.hpp"

class		ProtocolLobby : public IProtocolAction
{
private:
  typedef bool (ProtocolLobby::*ptr_functlobby)(PacketData &, User *, Server &);
  std::map<eProtocolPacketLobby, ptr_functlobby>	actionmap;

public:

  ProtocolLobby(void);
  ~ProtocolLobby(void);
  ProtocolLobby(const ProtocolLobby&);
  ProtocolLobby&	operator=(const ProtocolLobby&);
  virtual void action(ushort instruction, PacketData &data, User *, Server&);

private:

  bool		actionError(PacketData &data, User *, Server &);
  bool		actionChat(PacketData &data, User *, Server &);
};

#endif	// PROTOCOLLOBBY_H_
