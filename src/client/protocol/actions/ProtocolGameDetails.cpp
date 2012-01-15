#include "ProtocolGameDetails.hpp"
#include "Client.hpp"

ProtocolGameDetails::ProtocolGameDetails(void)
{
  this->actionmap[PLAYERLOGIN]	= &ProtocolGameDetails::actionError;
  this->actionmap[SCORE]	= &ProtocolGameDetails::actionScore;
  this->actionmap[GETMAP]	= &ProtocolGameDetails::actionError;
  this->actionmap[PLAYERLIFE]	= &ProtocolGameDetails::actionPlayerLife;

  this->actionmap[PLAYERKILL]	= &ProtocolGameDetails::actionPlayerKill;
  this->actionmap[MONSTERKILL]	= &ProtocolGameDetails::actionMonsterKill;

  this->actionmap[GAMEDATAIL_ERROR] = &ProtocolGameDetails::actionError;
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

bool ProtocolGameDetails::action(ushort instruction, PacketData &data, Client &client)
{
  std::map<eProtocolPacketGameDetails, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= GAME_DETAILS_MAX)
    (void)this->actionError(data, client);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGameDetails>(instruction))) ==
      this->actionmap.end())
    {
      (void)this->actionError(data, client);
      return false;
    }
  ptr = it->second;
  return ((this->*ptr)(data, client));
}

bool ProtocolGameDetails::actionError(PacketData &data, Client &)
{
  (void)data;
  return (false);
}

bool ProtocolGameDetails::actionScore(PacketData &data, Client &c)
{
  short i = 0;
  short nb;
  char id_player;
  std::string login;
  short score;
  std::string name;

  nb = data.getNextShort();
  while (i < nb)
    {
      id_player = data.getNextChar();
      login = data.getNextString();
      score = data.getNextShort();
      if (login == c.getGraphic().getLogin())
	{
	  c.getGraphic().setScore(score);
	}
      ++i;
    }
  return (false);
}

bool ProtocolGameDetails::actionPlayerLife(PacketData &data, Client &c)
{
  short i = 0;
  short nb;
  char id_player;
  std::string login;
  short lives;
  std::string name;

  nb = data.getNextShort();
  while (i < nb)
    {
      id_player = data.getNextChar();
      login = data.getNextString();
      lives = data.getNextShort();
      if (login == c.getGraphic().getLogin())
	{
	  c.getGraphic().setLives(lives);
	}
      ++i;
    }
  return (false);
}

bool ProtocolGameDetails::actionPlayerKill(PacketData &data, Client &)
{
  char id_player;
  std::string login;
  char killtype; // 0 = missile kill // 1 = collision kill

  id_player = data.getNextChar();
  login = data.getNextString();
  killtype = data.getNextChar();

  // idriss todo -> ici il faut afficher une explosion a lendroit
  // ou se trouve le id_player
  // killtype: 1= explosion big. 0= explostion circle
  return (false);
}

bool ProtocolGameDetails::actionMonsterKill(PacketData &data, Client &)
{
  char id_monstre;
  char killtype; // peut que mourrir dun missile... mais au cas ou

  id_monstre = data.getNextChar();
  killtype = data.getNextChar();

  // idriss todo -> ici il faut afficher une explosion a lendroit
  // ou se trouve le id_monstre
  // explostion : little_explostion
  return (false);
}
