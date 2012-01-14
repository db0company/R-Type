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
  this->_param.sizeLine = 15;
  this->_param.sizeCol = 7;
  this->_idPlayers = 0;
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
  this->_param.sizeLine = old._param.sizeLine;
  this->_param.sizeCol = old._param.sizeCol;
  this->_mutex = old._mutex;
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
  this->_param.sizeLine = old._param.sizeLine;
  this->_param.sizeCol = old._param.sizeCol;
  this->_mutex = old._mutex;
  return (*this);
}


void	Game::sendToAllClient(PacketData *data, eProtocolPacketGroup g, ushort fonc)
{
  ProtocolPacket *packet_to_send = PacketFactory::createPacket(g, fonc, data);
  std::map<std::string , User *>::iterator it2 = this->_userMap.begin();

  // std::cout << "debut 1" << std::endl;
  for (; it2 != _userMap.end(); ++it2)
    {
      // std::cout << "jai " << it2->second->getIp() << std::endl;
      if (it2->second->isSafe())
	it2->second->addPacketToSend(packet_to_send);
    }
  // std::cout << "fin 1" << std::endl;
}

void	Game::sendToIp(PacketData *data, eProtocolPacketGroup g, ushort fonc, Player *player)
{
  ProtocolPacket *packet_to_send = PacketFactory::createPacket(g, fonc, data);
  User	*us;

  us = static_cast<Player *>(player)->getUser();
  us->addPacketToSendUDP(packet_to_send);
}

void	Game::verifPos(Position& pos)
{
  while (true)
    {
      if (pos.x >= 0 && pos.x < 112 && pos.y >= 0 && pos.y < 150)
	  break;
      if (pos.x >= 112)
	{
	  pos.x -= 112;
	  pos.tilex += 1;
	}
      else if (pos.x < 0)
	{
	  pos.x += 112;
	  pos.tilex -= 1;
	}
      if (pos.y >= 150)
	{
	  pos.y -= 150;
	  pos.tiley += 1;
	}
      else if (pos.y < 0)
	{
	  pos.y += 150;
	  pos.tiley -= 1;
	}
    }
}

void	Game::initPos(Position &pos)
{
  pos.tilex = 0;
  pos.tiley = 0;
  pos.x = 400;
  pos.y = 400;
  verifPos(pos);
}

void	Game::changePlayerPos(GameParam& par)
{
  std::string ip;
  std::string ret;
  std::map<std::string, AObject *>::iterator it;
  Position newPos;
  Position direction;
  PacketData	*data= new PacketData;
  int		finalx;
  int		finaly;

  ip = par.us->getIp();
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
  direction.x = par.paDa->getNextChar();
  direction.y = par.paDa->getNextChar();
  // std::cout << " je bouge " << ret << " de " << direction.x << " " << direction.y << std::endl;

  if (direction.x == -1)
    newPos.x -= 8;
  else if (direction.x == 1)
    newPos.x += 8;
  if (direction.y == -1)
    newPos.y += 8;
  else if (direction.y == 1)
    newPos.y -= 8;
  verifPos(newPos);

  finalx = newPos.x + (newPos.tilex * 112);
  finaly = newPos.y + (newPos.tiley * 150);
  if (finalx < 0 || finalx > 1680 || finaly < 0 || finaly > 1050)
    {
      initPos(newPos);
      it->second->setPos(newPos);
      data->addChar(reinterpret_cast<Player *>(it->second)->getId());
      data->addString(it->first);
      data->addUint32(finalx);
      data->addUint32(finaly);
      sendToAllClient(data, MOVEMENT, COLLISION);
    }
  else
    {
      it->second->setPos(newPos);
      data->addChar(reinterpret_cast<Player *>(it->second)->getId());
      data->addString(it->first);
      data->addUint32(finalx);
      data->addUint32(finaly);
      //  std::cout << "jenvoi x " << newPos.x + (newPos.tilex * 112) << " y " << newPos.y + (newPos.tiley * 150) << std::endl;
      // [id du player][nom][int pos X graphic][int pos Y graphic]//    [vecteur x][vercteur y]
      sendToAllClient(data, MOVEMENT, UPDATEPLAYER);
    }
}

void	Game::createNewPlayer(User *us, const std::string& name)
{
  Player	*newPlayer = new Player(us, name);
  PacketData	*data = new PacketData;
  Position	pos;

  newPlayer->setId(this->_idPlayers);
  // std::cout << "my new friend is " << name << " with ip "<< us->getIp() << std::endl;
  pos.x = 400;
  pos.y = 400;// + (70 * newPlayer->getId());
  verifPos(pos);
  //  std::cout << "FIRST POS pos.x " << pos.x << " pos.y " << pos.y << "pos.tile x " << pos.tilex << " pos.tiley " << pos.tiley << std::endl;

  newPlayer->setPos(pos);
  this->_idPlayers++;
  this->_players.insert(std::pair<std::string, AObject *>(name, newPlayer));

}

void	Game::createNewMonster(GameParam&)
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
void	Game::moveMonster(GameParam& par)
{
  std::map<std::string, AObject *>::iterator it = this->_monster.begin();
  Position p;
  PacketData	*data = new PacketData;
  int		finalx;
  int		finaly;

  if (this->_monster.size() > 0)
    {
      data->addUint32(this->_monster.size());
      while (it != this->_monster.end())
	{
	  reinterpret_cast<Monster *>(it->second)->moveNextPos();
	  p = it->second->getPos();
	  verifPos(p);
	  it->second->setPos(p);
	  data->addString(it->first);
	  finalx = p.x + (p.tilex * 112);
	  finaly = p.y + (p.tiley * 150);
	  data->addUint32(finalx);
	  data->addUint32(finaly);
	  ++it;
	}
      sendToAllClient(data, MOVEMENT, UPDATEENEMY);
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

void	Game::checkCollision(GameParam&)
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

void	Game::fireBullet(GameParam& par)
{
  Entities	*ent;
  eGroup	g;
  Position	p;
  PacketData *data = new PacketData;
  int		finalx;
  int		finaly;

  // std::cout << "jenvoi bullet " << std::endl;

  if ((ent = reinterpret_cast<Entities *>
       (getEntitiesbyName(par.paDa->getNextString()))) == NULL)
    return ; // error
  g = ent->getGroup();
  p = ent->getPos();
  p.x += 30;
  p.y += 20;
  verifPos(p);
  this->_bullets.push_front(Bullet(p, g));

  finalx = p.x + (p.tilex * 112);
  finaly = p.y + (p.tiley * 150);
  data->addUint32(1);
  data->addUint32(finalx);
  data->addUint32(finaly);
  sendToAllClient(data, MOVEMENT, UPDATEBULLET);
}

void	Game::moveBullet(GameParam&)
{
  Position p;
  PacketData	*data = new PacketData;
  std::list<Bullet>::iterator it = this->_bullets.begin();
  int		finalx;
  int		finaly;

  if (this->_bullets.size() > 0)
    {
      data->addUint32(this->_bullets.size());
      while (it != this->_bullets.end())
	{
	  p = (*it).getPos();
	  if ((*it).getGroup() == ENNEMY)
	    p.x -= 14;
	  else
	    p.x += 14;
	  verifPos(p);
	  finalx = p.x + (p.tilex * 112);
	  finaly = p.y + (p.tiley * 150);
	  if (finalx < 0 || finalx > 1680 || finaly < 0 || finaly > 1050)
	    (*it).setDestroy();
	  (*it).setPos(p);
	  data->addUint32(finalx);
	  data->addUint32(finaly);
	  ++it;
	}
      it = this->_bullets.begin();
      while (it != this->_bullets.end())
	{
	  if (it->getDestroy() == true)
	    {
	      this->_bullets.erase(it);
	      it = this->_bullets.begin();
	    }
	  ++it;
	}
      sendToAllClient(data, MOVEMENT, UPDATEBULLET);
    }
}


AObject		*Game::getEntitiesbyName(const std::string& name)
{
  std::map<std::string, AObject *>::iterator it = this->_players.begin();

  while (it != this->_players.end())
    {
      if (it->first == name)
	return (it->second);
      ++it;
    }
  it = this->_monster.begin();
  while (it != this->_monster.end())
    {
      if (it->first == name)
	return (it->second);
      ++it;
    }
  return (NULL);
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

int		Game::nbBullet()
{
  return (this->_bullets.size());
}
