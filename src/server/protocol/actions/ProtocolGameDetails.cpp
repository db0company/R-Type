#include <iostream>
#include "PacketFactory.hpp"
#include "ProtocolPacket.h"
#include "ProtocolGameDetails.hpp"
#include "HighScore.hpp"
#include "User.hpp"

ProtocolGameDetails::ProtocolGameDetails(void)
{
  this->actionmap[GAMEDATAIL_ERROR] = &ProtocolGameDetails::actionError;
  this->actionmap[PLAYERLOGIN]	= &ProtocolGameDetails::actionPlayerLogin;
  this->actionmap[SCORE]	= &ProtocolGameDetails::actionScore;
  this->actionmap[GETMAP]	= &ProtocolGameDetails::actionGetMap;
  this->actionmap[RANKINGS]	= &ProtocolGameDetails::actionRankings;
  this->actionmap[PLAYERLIFE]	= &ProtocolGameDetails::actionError;
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
  return (false);
}

bool ProtocolGameDetails::actionRankings(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  HighScore		hg;
  std::vector<std::string> vec;
  std::vector<std::string>::iterator it;

  vec = hg.getListScore();
  it = vec.begin();
  to_send->addShort(vec.size());
  while (it != vec.end())
    {
      to_send->addString(*it);
      ++it;
    }
  packet_to_send = PacketFactory::createPacket(GAME_DETAILS, static_cast<ushort>(RANKINGS), to_send);
  user->addPacketToSend(packet_to_send);
  return (false);
}

bool ProtocolGameDetails::actionPlayerLogin(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  // TODO:
  // to_send: [nb_player(char)][playerlogin(string)]+
  packet_to_send = PacketFactory::createPacket(GAME_DETAILS, static_cast<ushort>(PLAYERLOGIN), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool ProtocolGameDetails::actionScore(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;

  // TODO:
  // to_send: [nb_player(char)][score(short)]
  // si le user fait partie dune game: get le score et lui envoyer. sinon rien envoyer
  packet_to_send = PacketFactory::createPacket(GAME_DETAILS, static_cast<ushort>(SCORE), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool ProtocolGameDetails::actionGetMap(PacketData &, User *, Server &)
{
  // BIG TODO: !!
  // What should i do ?
 return (true);
}
