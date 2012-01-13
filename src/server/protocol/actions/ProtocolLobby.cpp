#include <iostream>
#include "PacketFactory.hpp"
#include "ProtocolPacket.h"
#include "ProtocolLobby.hpp"
#include "User.hpp"
#include "Game.hpp"

ProtocolLobby::ProtocolLobby()
{
  this->actionmap[CHAT] = &ProtocolLobby::actionChat;
  this->actionmap[LOBBY_ERROR] = &ProtocolLobby::actionError;
  this->actionmap[LOBBY_PLAYERS] = &ProtocolLobby::actionError;
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

bool			ProtocolLobby::actionChat(PacketData & data, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::string msg;
  std::string login;

  login = data.getNextString();
  msg = data.getNextString();
  std::cout << "login(" << login << ")" << std::endl;
  std::cout << "chat_msg(" << msg << ")" << std::endl;
  if (msg.size())
    {
      to_send->addString(login);
      to_send->addString(msg);
      packet_to_send = PacketFactory::createPacket(LOBBY, static_cast<ushort>(CHAT), to_send);
      std::cout << user->getIp() << login << std::endl;
      if (user->getGame() && user->getState() != USER_ROOMLIST)
	{
	  std::map<std::string, User *> &umap = user->getGame()->getUserMap();
	  std::map<std::string, User *>::iterator it;
	  for (it = umap.begin(); it != umap.end(); ++it)
	    {
	      std::cout << "list player "<< it->first << std::endl;
	      it->second->addPacketToSend(packet_to_send);
	    }
	}
    }
  return (false);
}
