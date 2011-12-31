#include		<iostream>
#include		"ProtocolLobby.hpp"

ProtocolLobby::ProtocolLobby()
{
  this->actionmap[CHAT] = &ProtocolLobby::actionChat;
  this->actionmap[LOBBY_ERROR] = &ProtocolLobby::actionError;
}

ProtocolLobby::ProtocolLobby(ProtocolLobby const & other)
{
  this->actionmap = other.actionmap;
}

ProtocolLobby &		ProtocolLobby::operator=(ProtocolLobby const & other)
{
  if (&other != this)
    {
      this->actionmap = other.actionmap;
    }
  return (*this);
}

ProtocolLobby::~ProtocolLobby(void)
{
}

void			ProtocolLobby::action(ushort instruction,
					      PacketData & data, User *user, Server &serv)
{
  std::map<eProtocolPacketLobby, ptr_functlobby>::iterator it;
  ptr_functlobby	ptr;

  if (instruction >= LOBBY_MAX)
    (void)this->actionError(data, user, serv);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketLobby>(instruction))) == this->actionmap.end())
    {
      this->actionError(data, user, serv);
      return ;
    }
  ptr = it->second;
  (this->*ptr)(data, user, serv);
}

bool			ProtocolLobby::actionError(PacketData &, User *, Server &)
{
  return (false);
}

bool			ProtocolLobby::actionChat(PacketData & data, User *, Server &)
{
  (void)data;
  return (true);
}
