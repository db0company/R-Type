#include	"ProtocolGameDetails.hpp"

ProtocolGameDetails::ProtocolGameDetails(void)
{
  this->actionmap[PLAYERLOGIN]	= &ProtocolGameDetails::actionPlayerLogin;
  this->actionmap[SCORE]	= &ProtocolGameDetails::actionScore;
  this->actionmap[GETMAP]	= &ProtocolGameDetails::actionGetMap;
  this->actionmap[PLAYERLIFE]	= &ProtocolGameDetails::actionPlayerLife;
}

ProtocolGameDetails::ProtocolGameDetails(ProtocolGameDetails const &)
{
}

ProtocolGameDetails & ProtocolGameDetails::operator=(ProtocolGameDetails const &)
{
  return (*this);
}

ProtocolGameDetails::~ProtocolGameDetails(void)
{
}

void ProtocolGameDetails::action(ushort instruction, PacketData &data)
{
  std::map<eProtocolPacketGameDetails, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= GAME_DETAILS_MAX)
    (void)this->actionError(data);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGameDetails>(instruction))) ==
      this->actionmap.end())
    (void)this->actionError(data);
  ptr = it->second;
  (this->*ptr)(data);
}

bool ProtocolGameDetails::actionError(PacketData &data)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionPlayerLogin(PacketData &data)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionScore(PacketData &data)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionGetMap(PacketData &data)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionPlayerLife(PacketData &data)
{
  (void)data;
  return (true);
}

