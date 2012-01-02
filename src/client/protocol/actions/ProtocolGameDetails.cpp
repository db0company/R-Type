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

void ProtocolGameDetails::action(ushort instruction, PacketData &data, Client &client)
{
  std::map<eProtocolPacketGameDetails, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= GAME_DETAILS_MAX)
    (void)this->actionError(data, client);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGameDetails>(instruction))) ==
      this->actionmap.end())
    {
      (void)this->actionError(data, client);
    return;
    }
  ptr = it->second;
  (this->*ptr)(data, client);
}

bool ProtocolGameDetails::actionError(PacketData &data, Client &)
{
  (void)data;
  return (true);
}

bool ProtocolGameDetails::actionPlayerLogin(PacketData &data, Client &)
{
  short i = 0;
  short nb_player;
  std::string name;

  nb_player = data.getNextShort();
  if (!nb_player)
    return (false);
  while (i < nb_player)
    {
      name = data.getNextString();
      // TODO: add la string au data de la game
      ++i;
    }
  return (true);
}

bool ProtocolGameDetails::actionScore(PacketData &data, Client &)
{
  short i = 0;
  short nb_player;
  short score;
  std::string name;

  nb_player = data.getNextShort();
  if (!nb_player)
    return (false);
  while (i < nb_player)
    {
      name = data.getNextString();
      score = data.getNextShort();
      // TODO: modif le score du player
      ++i;
    }
  return (true);
}

bool ProtocolGameDetails::actionGetMap(PacketData &, Client &)
{
  // TODO a definir
  return (true);
}

bool ProtocolGameDetails::actionPlayerLife(PacketData &data, Client &)
{
  char id_player;
  char lives;

  id_player = data.getNextChar();
  lives = data.getNextChar();
  // TODO: update les vie du player.
  return (true);
}

