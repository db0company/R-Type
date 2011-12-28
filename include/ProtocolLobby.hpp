#ifndef PROTOCOLLOBBY_H_
# define PROTOCOLLOBBY_H_

# include	<map>
# include	"iProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketLobby.hpp"

class		ProtocolLobby : public iProtocolAction
{
private:
  typedef bool (ProtocolLobby::*ptr_funct)(PacketData &);
  std::map<eProtocolPacketLobby, ptr_funct>	actionmap;

public:

  ProtocolLobby(void);
  ~ProtocolLobby(void);
  ProtocolLobby(const ProtocolLobby&);
  ProtocolLobby&	operator=(const ProtocolLobby&);
  virtual void action(ushort instruction, PacketData &data);

private:

  bool		actionError(PacketData &data);
  bool		actionChat(PacketData &data);
};

#endif	// PROTOCOLLOBBY_H_
