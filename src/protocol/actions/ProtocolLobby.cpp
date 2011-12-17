#include		"ProtocolLobby.hpp"

ProtocolLobby::ProtocolLobby()
{
  this->actionmap[LOBBY_ERROR] = &ProtocolLobby::actionError;
  this->actionmap[CHAT] = &ProtocolLobby::actionChat;
}

ProtocolLobby::ProtocolLobby(ProtocolLobby const & other)
{
  (void)other;
}

ProtocolLobby &		ProtocolLobby::operator=(ProtocolLobby const & other)
{
  if (&other != this)
    {
    }
  return (*this);
}

ProtocolLobby::~ProtocolLobby(void)
{
}

void			ProtocolLobby::action(ushort instruction,
					     PacketData & data)
{
  std::map<eProtocolPacketLobby, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= LOBBY_MAX)
    (void)this->actionError(data);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketLobby>(instruction))) == this->actionmap.end())
    (void)this->actionError(data);
  ptr = it->second;
  (this->*ptr)(data);
  //  (void)((this->*actionmap[static_cast<eProtocolContact>(instruction)]) //oldx
}

bool			ProtocolLobby::actionError(PacketData &)
{
  return (true);
}

bool			ProtocolLobby::actionChat(PacketData & data)
{
  (void)data;
  return (true);
}
