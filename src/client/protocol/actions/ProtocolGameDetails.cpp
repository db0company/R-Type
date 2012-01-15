#include "ProtocolGameDetails.hpp"
#include "Client.hpp"
#include "IAnnim.hpp"
#include "AnnimCircleExplosion.hpp"
#include "AnnimBigExplosion.hpp"
#include "AnnimLittleExplosion.hpp"
#include "AMonsterMovement.hpp"
#include "PlayerMovement.hpp"

ProtocolGameDetails::ProtocolGameDetails(void)
{
  this->actionmap[PLAYERLOGIN]	= &ProtocolGameDetails::actionError;
  this->actionmap[SCORE]	= &ProtocolGameDetails::actionScore;
  this->actionmap[GETMAP]	= &ProtocolGameDetails::actionError;
  this->actionmap[PLAYERLIFE]	= &ProtocolGameDetails::actionPlayerLife;

  this->actionmap[PLAYERKILL]	= &ProtocolGameDetails::actionPlayerKill;
  this->actionmap[MONSTERKILL]	= &ProtocolGameDetails::actionMonsterKill;
  this->actionmap[RANKINGS]	= &ProtocolGameDetails::actionRankings;

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

bool ProtocolGameDetails::actionRankings(PacketData &data, Client &c)
{
  std::list<std::string> & map = c.getGraphic().getRankingList();
  unsigned int nbRank = data.getNextShort();
  unsigned int i = 0;
  map.clear();
  while (i < nbRank)
    {
      map.push_back(data.getNextString());
      ++i;
    }
  // if (!map.empty())
  //   for (std::list<std::string>::const_iterator it = map.begin();
  // 	 it != map.end(); ++it)
  //     std::cout << (*it) << std::endl;
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

bool ProtocolGameDetails::actionPlayerKill(PacketData &data, Client &c)
{
  char id_player;
  std::string login;
  char killtype; // 0 = missile kill // 1 = collision kill
  int posx;
  int posy;
  LibGraphic::IAnnim *e;
  std::list<LibGraphic::IAnnim *> &map = c.getGraphic().getExplosionList();
  std::map<int, LibGraphic::PlayerMovement *> &playerMap = c.getGraphic().getPlayerMap();
  id_player = data.getNextChar();
  login = data.getNextString();
  killtype = data.getNextChar();
  posx = data.getNextShort();
  posy = data.getNextShort();

  if (killtype == 0)
    {
      e = new LibGraphic::AnnimCircleExplosion(c.getGraphic().getWindow(),
					       c.getGraphic().getSprite("CircleExplosion"));
      LibGraphic::MySound * song = c.getGraphic().getSound("PlayerExplo");
      song->PlaySound();
    }
  else
    {
      e = new LibGraphic::AnnimBigExplosion(c.getGraphic().getWindow(),
					    c.getGraphic().getSprite("BigExplosion"));
      LibGraphic::MySound * song = c.getGraphic().getSound("PlayerExplo");
      song->PlaySound();
    }
  e->setCoord(posx, posy);
  map.push_front(e);
  if (playerMap.find(id_player) != playerMap.end())
    playerMap.erase(id_player);
  return (false);
}

bool ProtocolGameDetails::actionMonsterKill(PacketData &data, Client &c)
{
  char id_monstre;
  char killtype;
  int posx;
  int posy;
  LibGraphic::IAnnim *e;
  std::list<LibGraphic::IAnnim *> &map = c.getGraphic().getExplosionList();
  std::map<int, LibGraphic::AMonsterMovement *> &monsters = c.getGraphic().getMonsterMap();

  id_monstre = data.getNextChar();
  killtype = data.getNextChar(); // ignored pour le moment. ou pas
  posx = data.getNextShort();
  posy = data.getNextShort();
  if (killtype == 0)
    {
      e = new LibGraphic::AnnimLittleExplosion(c.getGraphic().getWindow(),
	c.getGraphic().getSprite("LittleExplosion"));
      e->setCoord(posx, posy);
      map.push_front(e);
    }
  if (monsters.find(id_monstre) != monsters.end())
    monsters.erase(id_monstre);
  return (false);
}
