#include	"ProtocolGameDetails.hpp"

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

bool ProtocolGameDetails::actionError(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionPlayerLogin(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionScore(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionGetMap(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionPlayerLife(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

