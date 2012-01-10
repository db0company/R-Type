#include <iostream>
#include <map>
#include <string>
#include "Player.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Game.hpp"
#include "User.hpp"
#include "User.hpp"
#include "eProtocolPacketMovement.hpp"
#include "eProtocolPacketGame.hpp"
#ifdef _WIN32
#include "MutexWindows.hpp"
#else
#include "MutexUnix.hpp"
#endif

unsigned int Game::_sid = 0;

Game::Game() : _owner_login(""), _name(""), _lvlname(""), player_max(4),
	       _observer(true), _status(LOBBYROOM)
{
  // On va faire quelques tests.

  // createNewPlayer(NULL, "Player1");
  // createNewPlayer(NULL, "Player2");
  // createNewMonster(NULL);
  // createNewMonster(NULL);
  // createWall();

  //  _rMap.recupFromFile("nom_du_level.txt");
  this->_id = this->_sid;
  ++(this->_sid);
#ifdef _WIN32
  this->_mutex = new MutexWindows;
#else
  this->_mutex = new MutexUnix;
#endif
}

Game::~Game()
{

}

Game::Game(const Game& old)
{
  this->_id = old._id;
  this->_param = old._param;
  this->_players = old._players;
  this->_monster = old._monster;
  this->_map = old._map;
  this->_bullets = old._bullets;
  this->_userMap = old._userMap;
  this->_owner_login = old._owner_login;
  this->_name = old._name;
  this->_lvlname = old._lvlname;
  this->player_max = old.player_max;
  this->_observer = old._observer;
  this->_status = old._status;
}

Game&	Game::operator=(const Game& old)
{
  this->_id = old._id;
  this->_param = old._param;
  this->_players = old._players;
  this->_monster = old._monster;
  this->_map = old._map;
  this->_bullets = old._bullets;
  this->_userMap = old._userMap;
  this->_owner_login = old._owner_login;
  this->_name = old._name;
  this->_lvlname = old._lvlname;
  this->player_max = old.player_max;
  this->_observer = old._observer;
  this->_status = old._status;
  return (*this);
}


void	Game::sendToAllClient(PacketData *data, eProtocolPacketGroup g, ushort fonc)
{
  std::map<std::string, AObject*>::const_iterator it = this->_players.begin();
  User	*us;

  while (it != this->_players.end())
    {
      ProtocolPacket *packet_to_send = PacketFactory::createPacket(g, fonc, data);
      us = static_cast<Player *>(it->second)->getUser();
      us->addPacketToSendUDP(packet_to_send);
      ++it;
    }
}

void	Game::sendToIp(PacketData *data, eProtocolPacketGroup g, ushort fonc, Player *player)
{
  ProtocolPacket *packet_to_send = PacketFactory::createPacket(g, fonc, data);
  User	*us;

  us = static_cast<Player *>(player)->getUser();
  us->addPacketToSendUDP(packet_to_send);
}

void	Game::changePlayerPos(PacketData &info)
{
  std::string ip; // a extraire du packet
  std::string ret;
  std::map<std::string, AObject *>::iterator it;
  Position newPos;
  PacketData	*data = new PacketData;

  if ((ret = getPlayerByIp(ip)) == "")
    {
      // error player inconnu
      return ;
    }
  it = this->_players.find(ret);
  if (it == this->_players.end())
    {
      // error player inconnu
      return ;
    }
  newPos = it->second->getPos();
  //  newPos = info.getPosition();
  it->second->setPos(newPos);
  data->addString(it->first);
  //  data->addData<Position>(it->second->getPos);
  sendToAllClient(data, MOVEMENT, UPDATEPLAYER);
}

void	Game::moveMonster(PacketData&)
{
  std::map<std::string, AObject *>::iterator it = this->_monster.begin();

  while (it != this->_monster.end())
    {
      PacketData	*data = new PacketData;

      reinterpret_cast<Monster *>(it->second)->moveNextPos();
      data->addString(it->first);
      //data->addData<Position>(it->second->getPos());
      sendToAllClient(data, MOVEMENT, UPDATEENEMY);
      ++it;
    }
}

void	Game::createNewPlayer(User *us, const std::string& name)
{
  Player	*newPlayer = new Player(us, name);
  PacketData	*data = new PacketData;
  Position	pos;

  this->_players.insert(std::pair<std::string, AObject *>(name, newPlayer));
}

void	Game::createNewMonster(PacketData &)
{
  AObject *truc;
  int	i = 0;
  std::string name;
  PacketData *data = new PacketData;

  while (i != 3)
    {
      truc = new Monster;
      // initialisation du monstre
      this->_monster.insert(std::pair<std::string, AObject *>("monster", truc));
      data->addString("monster01");
      //      data->addData<Position>(newPos);
      sendToAllClient(data, MOVEMENT, UPDATEENEMY);
      ++i;
    }

}

const std::string& Game::getPlayerByIp(const std::string& ip)
{
  std::map<std::string, AObject *>::iterator it = this->_players.begin();

  while (it != this->_players.end())
    {
      if (reinterpret_cast<Player *>(it->second)->getIp() == ip)
	return (it->second->getName());
      ++it;
    }
  //error
  return (it->second->getName()); // jai mis sa pour retirer le warning
}

void	Game::checkCollision(PacketData &)
{
  std::map<std::string, AObject *>::iterator itP = this->_players.begin();
  std::map<std::string, AObject *>::iterator itM = this->_monster.begin();
  std::list<Bullet>::iterator itB = this->_bullets.begin();

  while (itP != this->_players.end())
    {
      itM = this->_monster.begin();
      while (itB != this->_bullets.end())
	{

	  if ((*itB).getGroup() == ENNEMY && itP->second->getPos() == (*itB).getPos())
	    {
	      PacketData *data = new PacketData;

	      data->addString(itP->first);
	      sendToAllClient(data, THE_GAME, ENDGAME);
	      // kill player; NE PAS DETRUIRE LE MAILLON ICI
	      // destroy la bullet MAIS PAS ICI
	    }
	  ++itM;
	}
      while (itM != this->_monster.end())
	{
	  if (itP->second->getPos() == itM->second->getPos())
	    {
	      PacketData *data = new PacketData;

	      data->addString(itP->first);
	      sendToAllClient(data, THE_GAME, ENDGAME);
	      // kill player; NE PAS DETRUIRE LE MAILLON ICI
	    }
	  ++itM;
	}
      ++itP;
    }
}

void	Game::moveBullet(PacketData &)
{
  Position p;
  std::list<Bullet>::iterator it = this->_bullets.begin();

  while (it != this->_bullets.end())
    {
      PacketData	*data = new PacketData;

      p = (*it).getPos();
      p.x--;
      //      data->addData<Position>(it->getPos());
      sendToAllClient(data, MOVEMENT, UPDATEBULLET);
      (*it).setPos(p);
      ++it;
    }
}

void	Game::moveWall(PacketData &)
{
  std::list<AObject *> line;

  line = this->_map.front();
  this->_map.pop_front();
  //faire des modifs sur wall pour faire croire a un new mur
  this->_map.push_front(line);
}

void	Game::createWall()
{
  std::list<AObject *> newLine;
  int	i = 0;
  int	j;
  TileStruct ts;

  while (i != this->_param.sizeCol)
    {
      j = 0;
      ts = _rMap[i];
      while (j != this->_param.sizeLine)
	{
	  if (j == 0)
	    newLine.push_front(new Tile(ts.up));
	  else if (j == this->_param.sizeLine - 1)
	    newLine.push_front(new Tile(ts.down));
	  else
	    newLine.push_front(new Tile(TileEmpty));
	  ++j;
	}
      ++i;
      this->_map.push_back(newLine);
    }
}

void	Game::fireBullet(PacketData &)
{
  AObject *ent = NULL;
  eGroup	g;
  PacketData *data = new PacketData;

  g = reinterpret_cast<Entities *>(ent)->getGroup();
  this->_bullets.push_front(Bullet(ent->getPos(), g));
  //  data->addData<Position>(ent->getPos());
  sendToAllClient(data, MOVEMENT, UPDATEBULLET);
}

bool Game::addUser(User *user, bool root, bool , std::string const &login)
{
  if (this->_userMap.size() > this->player_max)
    return (false);
  if (root)
    this->_owner_login = login;
  this->_userMap.insert(std::pair<std::string, User *>(user->getIp(), user));
  return (true);
}

bool Game::delUser(std::string const &log)
{
  this->_userMap.erase(log);
  return (true);
}

unsigned int Game::getId(void) const
{
  return (this->_id);
}

std::string &Game::getOwnerLogin(void)
{
  return (this->_owner_login);
}

void Game::setOwnerId(std::string const &log)
{
  this->_owner_login = log;
}

std::string &Game::getName(void)
{
  return (this->_name);
}

void Game::setName(std::string const &n)
{
  this->_name = n;
}

std::string &Game::getLvlName(void)
{
  return (this->_lvlname);
}

void Game::setLvlName(std::string const &lvl)
{
  this->_lvlname = lvl;
}

unsigned int Game::getPlayerMax(void)const
{
  return (this->player_max);
}
void Game::setPlayerMax(unsigned int p)
{
  this->player_max = p;
}

bool Game::getObs(void)const
{
  return (this->_observer);
}

void Game::setObs(bool o)
{
  this->_observer = o;
}

unsigned int Game::getNbPlayer(void)const
{
  return (this->_userMap.size());
}

IMutex		*Game::getMutex()
{
  return (this->_mutex);
}

std::map<std::string, AObject *>& Game::getPlayerList()
{
  return (this->_players);
}

void		Game::setStatus(eGameStatus e)
{
  this->_status = e;
}

eGameStatus	Game::getStatus(void)const
{
  return (this->_status);
}

std::map<std::string, User *> &Game::getUserMap()
{
  return (this->_userMap);
}
