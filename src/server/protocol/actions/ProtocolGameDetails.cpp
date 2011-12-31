#include <iostream>
#include "PacketFactory.hpp"
#include "ProtocolPacket.h"
#include "ProtocolGameDetails.hpp"
#include "User.hpp"

ProtocolGameDetails::ProtocolGameDetails(void)
{
  this->actionmap[PLAYERLOGIN]	= &ProtocolGameDetails::actionPlayerLogin;
  this->actionmap[SCORE]	= &ProtocolGameDetails::actionScore;
  this->actionmap[GETMAP]	= &ProtocolGameDetails::actionGetMap;
  this->actionmap[PLAYERLIFE]	= &ProtocolGameDetails::actionPlayerLife;
}

ProtocolGameDetails::ProtocolGameDetails(ProtocolGameDetails const &other)
{
  this->actionmap = other.actionmap;
}

ProtocolGameDetails & ProtocolGameDetails::operator=(ProtocolGameDetails const &other)
{
  this->actionmap = other.actionmap;
  return (*this);
}

ProtocolGameDetails::~ProtocolGameDetails(void)
{
}

void ProtocolGameDetails::action(ushort instruction, PacketData &data, User *user, Server &serv)
{
  std::map<eProtocolPacketGameDetails, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= GAME_DETAILS_MAX)
    (void)this->actionError(data, user, serv);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGameDetails>(instruction))) ==
      this->actionmap.end())
    {
      (void)this->actionError(data, user, serv);
    return;
    }
  ptr = it->second;
  (this->*ptr)(data, user, serv);
}

bool ProtocolGameDetails::actionError(PacketData &, User *, Server &)
{
  return (true);
}

bool ProtocolGameDetails::actionPlayerLogin(PacketData &, User *user, Server &)
{
  PacketData  to_send;
  ProtocolPacket *packet_to_send;
  // TODO:
  // to_send: [nb_player(char)][playerlogin(string)]+
  packet_to_send = PacketFactory::createPacket(GAME_DETAILS, static_cast<ushort>(PLAYERLOGIN), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool ProtocolGameDetails::actionScore(PacketData &, User *, Server &)
{
  // PacketData  to_send;
  // ProtocolPacket *packet_to_send;

  // TODO:
  // to_send: [nb_player(char)][score(short)]
  // si le user fait partie dune game: get le score et lui envoyer. sinon rien envoyer
  // packet_to_send = PacketFactory::createPacket(GAME_DETAILS, static_cast<ushort>(SCORE), to_send);
  // user->addPacketToSend(packet_to_send);
  return (true);
}

bool ProtocolGameDetails::actionGetMap(PacketData &, User *, Server &)
{
  // BIG TODO: !!
  // What should i do ?
 return (true);
}

bool ProtocolGameDetails::actionPlayerLife(PacketData &, User *, Server &)
{
  // nothing to do ;)
  return (true);
}
