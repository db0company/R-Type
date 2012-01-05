#include <iostream>
#include "PacketFactory.hpp"
#include "ProtocolPacket.h"
#include "ProtocolLobby.hpp"
#include "User.hpp"

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

bool			ProtocolLobby::actionChat(PacketData & data, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::string msg;

  msg = data.getNextString();
  std::cout << "chat_msg(" << msg << ")" << std::endl;
  if (msg.size())
    {
      // TODO:
      // verifier si le user est dans une game. que cette game n'a pas encore commencer
      // (lobby -mode). si c'est le cas et que le msg n'est pas vide: envoyer a tt les
      // client de cette game le packet.
      // to_send: [player_login(string)][msg(string)]
      to_send->addString("login"); // recup login todo
      to_send->addString(msg);
      packet_to_send = PacketFactory::createPacket(LOBBY, static_cast<ushort>(CHAT), to_send);
      user->addPacketToSend(packet_to_send); // pour tt les clients de la game
    }
  return (false);
}
