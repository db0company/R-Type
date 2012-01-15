#include <iostream>
#include <map>
#include <cstdlib>
#include <string>
#include "Player.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Game.hpp"
#include "User.hpp"
#include "User.hpp"
#include "eProtocolPacketMovement.hpp"
#include "eProtocolPacketGame.hpp"
#include "eProtocolPacketGameDetails.hpp"
#include "ScopedLock.hpp"
#include "DlLoader.hpp"
#include "OS.hpp"
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
  this->_monsterId = 0;
  this->_mapDll.insert(std::pair<int, std::string>(0, MONSTERBASE));
  this->_mapDll.insert(std::pair<int, std::string>(1, MONSTERSHIP));
  this->_mapDll.insert(std::pair<int, std::string>(2, MONSTEREYE));
  this->_mapDll.insert(std::pair<int, std::string>(3, MONSTERROBOT));
  this->_mapDll.insert(std::pair<int, std::string>(4, MONSTERCRAB));
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
  this->_monsterId = old._monsterId;
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
  this->_monsterId = old._monsterId;
  return (*this);
}


void	Game::sendToAllClient(PacketData *data, eProtocolPacketGroup g, ushort fonc)
{
  ProtocolPacket *packet_to_send = PacketFactory::createPacket(g, fonc, data);
  std::map<std::string , User *>::iterator it2 = this->_userMap.begin();

  for (; it2 != _userMap.end(); ++it2)
    if (it2->second->isSafe())
      it2->second->addPacketToSend(packet_to_send);
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
  short		finalx;
  short		finaly;

  ip = par.us->getIp();
  if ((ret = getPlayerByIp(ip)) == "")
    return ;
  it = this->_players.find(ret);
  if (it == this->_players.end() || static_cast<Entities *>(it->second)->isDie() == true)
    return ;
  newPos = it->second->getPos();
  direction.x = par.paDa->getNextChar();
  direction.y = par.paDa->getNextChar();

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
      dynamic_cast<Player *>(it->second)->changeLife(1);
      sendLooseLife(dynamic_cast<Player *>(it->second), 1);

      initPos(newPos);
      it->second->setPos(newPos);
      data->addChar(reinterpret_cast<Player *>(it->second)->getId());
      data->addString(it->first);
      data->addShort(finalx);
      data->addShort(finaly);
      sendToAllClient(data, MOVEMENT, COLLISION);
    }
  else
    {
      it->second->setPos(newPos);
      data->addChar(reinterpret_cast<Player *>(it->second)->getId());
      data->addString(it->first);
      data->addShort(finalx);
      data->addShort(finaly);
      sendToAllClient(data, MOVEMENT, UPDATEPLAYER);
    }
}

void	Game::sendEndPacket()
{
  PacketData	*data = new PacketData;

  sendToAllClient(data, THE_GAME, ENDGAME);
}

void	Game::launchWave(GameParam&)
{
  std::map<std::string, AObject *>::iterator it = this->_players.begin();
  GameParam gp(NULL, NULL);
  Monster	*mob;
  int	r = 0;
  Position p;
  int		i = 0;
  int		nbMob = 4;
  DlLoader	*dl = DlLoader::getInstance();
  std::string	str;
  std::cout << "new wave" << std::endl;

  while (it != this->_players.end())
    {
      if (static_cast<Entities *>(it->second)->isDie() == false)
	break;
      ++it;
    }
  if (it == this->_players.end())
    {
      this->_status = ENDED;
      sendEndPacket();
    }
  while (i != nbMob)
    {
      r = rand() % 5;
      dl->activMut();
      str = this->_mapDll[r];
      if (str != "")
	{
	  mob = dynamic_cast<Monster *>(dl->getDll(str).getSymbol<IObject>(GETMONSTER));
	  dl->desactivMut();
	  p.x = 1700;
	  p.y = 400 + 50 * i;
	  verifPos(p);
	  createNewMonster(p, mob);
	}
      ++i;
    }
}

void	Game::createNewPlayer(User *us, const std::string& name)
{
  ScopedLock sl(this->_mutex);

  Player	*newPlayer = new Player(us, name);
  PacketData	*data = new PacketData;
  Position	pos;

  newPlayer->setId(this->_idPlayers);
  pos.x = 400;
  pos.y = 400;
  verifPos(pos);
  newPlayer->setPos(pos);
  this->_idPlayers++;
  this->_players.insert(std::pair<std::string, AObject *>(name, newPlayer));

}

void	Game::createNewMonster(const Position& p, Monster *mob)
{
  PacketData *data = new PacketData;
  int		finalx;
  int		finaly;

  mob->setPos(p);
  mob->setMId(this->_monsterId);
  finalx = p.x + (p.tilex * 112);
  finaly = p.y + (p.tiley * 150);
  data->addChar(mob->getMId());
  data->addChar(mob->getMType());
  data->addShort(finalx);
  data->addShort(finaly);
  sendToAllClient(data, MOVEMENT, UPDATEENEMY);
  this->_monster.insert(std::pair<int, AObject *>(mob->getMId(), mob));
  this->_monsterId++;
}
void	Game::moveMonster(GameParam& par)
{
  std::map<int, AObject *>::iterator it = this->_monster.begin();
  Position p;

  short		finalx;
  short		finaly;
  Monster	*mob;

  if (this->_monster.size() > 0)
    {
      while (it != this->_monster.end())
	{
	  PacketData	*data = new PacketData;

	  mob = dynamic_cast<Monster *>(it->second);
	  mob->moveNextPos();
	  p = mob->getPos();
	  verifPos(p);
	  mob->setPos(p);
	  if (mob->wantFire() == true)
	    fireEnnemyBullet(mob);
	  finalx = p.x + (p.tilex * 112);
	  finaly = p.y + (p.tiley * 150);
	  if (finalx < -10)
	    {
	      static_cast<Entities *>(it->second)->die();
	      sendMonsterDeath(dynamic_cast<Monster *>(it->second), 1);
	      ++it;
	    }	    
	  data->addChar(mob->getMId());
	  data->addChar(mob->getMType());
	  data->addShort(finalx);
	  data->addShort(finaly);
	  ++it;
	  sendToAllClient(data, MOVEMENT, UPDATEENEMY);
	}
    }
  it = this->_monster.begin();
  while (it != this->_monster.end())
    {
      if (dynamic_cast<Entities *>(it->second)->isDie() == true)
	{
	  sendMonsterDeath(dynamic_cast<Monster *>(it->second), 0);
	  this->_monster.erase(it);
	  it = this->_monster.begin();
	}
      else
	++it;
    }
}

const std::string& Game::getPlayerByIp(const std::string& ip)
{
  std::map<std::string, AObject *>::iterator it = this->_players.begin();

  while (it != this->_players.end())
    {
      if (dynamic_cast<Player *>(it->second)->getIp() == ip)
	return (it->second->getName());
      ++it;
    }
  //error
  return (it->second->getName()); // jai mis sa pour retirer le warning
}

bool	Game::checkInTile(AObject *ob1, AObject *ob2)
{
  int	x1 = ob1->getPos().x;
  int	y1 = ob1->getPos().y;
  int	x2 = ob2->getPos().x;
  int	y2 = ob2->getPos().y;

  if (x1 - x2 < 60 && x1 - x2 > -60 && y1 - y2 < 30 && y1 - y2 > -30)
    return (true);
  return (false);
}

void	Game::refreshLivesPlayers()
{
  PacketData *data = new PacketData;
  std::map<std::string, AObject *>::const_iterator it = this->_players.begin();

  data->addShort(this->_players.size());
  while (it != this->_players.end())
    {
      data->addChar(dynamic_cast<Player *>(it->second)->getId());
      data->addString(it->second->getName().c_str());
      data->addShort(dynamic_cast<Entities *>(it->second)->getLife());
      ++it;
    }
  sendToAllClient(data, GAME_DETAILS, PLAYERLIFE);
}


void	Game::sendLooseLife(Player *play, char killtype)
{
  PacketData *data = new PacketData;
  Position	p = play->getPos();
  int		finalx;
  int		finaly;

  finalx = p.x + (p.tilex * 112);
  finaly = p.y + (p.tiley * 150);
  data->addChar(play->getId());
  data->addString(play->getName().c_str());
  data->addChar(killtype);
  data->addShort(finalx);
  data->addShort(finaly);
  sendToAllClient(data, GAME_DETAILS, PLAYERKILL);
  refreshLivesPlayers();
}

void	Game::sendMonsterDeath(Monster *mob, char killtype)
{
  PacketData *data = new PacketData;
  int		finalx;
  int		finaly;
  Position	p = mob->getPos();

  finalx = p.x + (p.tilex * 112);
  finaly = p.y + (p.tiley * 150);
  data->addChar(mob->getMId());
  data->addChar(killtype);
  data->addShort(finalx);
  data->addShort(finaly);
  sendToAllClient(data, GAME_DETAILS, MONSTERKILL);
}

void	Game::sendScore()
{
  PacketData *data = new PacketData;
  std::map<std::string, AObject *>::iterator it = this->_players.begin();

  data->addShort(this->_players.size());
  while (it != this->_players.end())
    {
      data->addChar(static_cast<Player *>(it->second)->getId());
      data->addString(static_cast<Player *>(it->second)->getName());
      data->addShort(static_cast<Player *>(it->second)->getScore());
      ++it;
    }
  sendToAllClient(data, GAME_DETAILS, SCORE);
}

void	Game::checkCollision(GameParam&)
{
  std::map<std::string, AObject *>::iterator itP = this->_players.begin();
  std::map<int, AObject *>::iterator itM = this->_monster.begin();
  std::list<Bullet>::iterator itB = this->_bullets.begin();
  std::map<std::string, AObject *>::iterator ret;
  while (itM != this->_monster.end())
    {
      itB = this->_bullets.begin();

      while (itB != this->_bullets.end())
	{
	  if (itB->getGroup() == FRIENDS && itB->getPos() == itM->second->getPos())
	    if (checkInTile(&(*itB), itM->second) == true)
	      {
		itB->setDestroy();
		ret = this->_players.find(itB->getOwner());
		if (ret != this->_players.end())
		  {
		    dynamic_cast<Player *>(ret->second)->AddToScore(10);
		    sendScore();
		  }
		dynamic_cast<Entities *>(itM->second)->die();
	      }
	  ++itB;
	}
      ++itM;
    }
  while (itP != this->_players.end())
    {
      itB = this->_bullets.begin();
      if (static_cast<Entities *>(itP->second)->isDie() == false)
	{
	  while (itB != this->_bullets.end())
	    {
	      if (itB->getGroup() == ENNEMY && itB->getPos() == itP->second->getPos())
		if (checkInTile(&(*itB), itP->second) == true)
		  {
		    itB->setDestroy();
		    dynamic_cast<Player *>(itP->second)->changeLife(1);
		    sendLooseLife(dynamic_cast<Player *>(itP->second), 1);
		  }
	      ++itB;
	    }
	}
      ++itP;
    }
  itM = this->_monster.begin();
  itP = this->_players.begin();
  while (itM != this->_monster.end())
    {
      itP = this->_players.begin();
      while (itP != this->_players.end())
	{
	  if (static_cast<Entities *>(itP->second)->isDie() == false && itP->second->getPos() == itM->second->getPos())
	    if (checkInTile(itP->second, itM->second) == true)
	      {
		dynamic_cast<Entities *>(itP->second)->changeLife(1);
		sendLooseLife(dynamic_cast<Player *>(itP->second), 1);
		dynamic_cast<Entities *>(itM->second)->die();
	      }
	  ++itP;
	}
      ++itM;
    }

  itM = this->_monster.begin();
  while (itM != this->_monster.end())
    {
      if (dynamic_cast<Entities *>(itM->second)->isDie() == true)
	{
	  sendMonsterDeath(dynamic_cast<Monster *>(itM->second), 0);
	  this->_monster.erase(itM);
	  itM = this->_monster.begin();
	}
      else
	++itM;
    }

  itB = this->_bullets.begin();
  while (itB != this->_bullets.end())
    {
      if (itB->getDestroy() == true)
	{
	  this->_bullets.erase(itB);
	  itB = this->_bullets.begin();
	}
      ++itB;
    }
}

void	Game::fireEnnemyBullet(Monster *ent)
{
  eGroup	g;
  Position	p;
  PacketData *data = new PacketData;
  short		finalx;
  short		finaly;

  // std::cout << "jenvoi bullet " << std::endl;

  g = ent->getGroup();
  p = ent->getPos();
  p.x -= 30;
  verifPos(p);
  this->_bullets.push_front(Bullet(p, g, ""));
  finalx = p.x + (p.tilex * 112);
  finaly = p.y + (p.tiley * 150);
  data->addShort(1);
  data->addShort(finalx);
  data->addShort(finaly);
  sendToAllClient(data, MOVEMENT, UPDATEBULLET);
}

void	Game::fireBullet(GameParam& par)
{
  Entities	*ent;
  eGroup	g;
  Position	p;
  PacketData *data = new PacketData;
  short		finalx;
  short		finaly;

  if ((ent = dynamic_cast<Entities *>
       (getEntitiesbyName(par.paDa->getNextString()))) == NULL ||
      ent->isDie() == true)
    return ;
  g = ent->getGroup();
  p = ent->getPos();
  p.x += 30;
  p.y += 20;
  verifPos(p);
  this->_bullets.push_front(Bullet(p, g, ent->getName()));
  finalx = p.x + (p.tilex * 112);
  finaly = p.y + (p.tiley * 150);
  data->addShort(1);
  data->addShort(finalx);
  data->addShort(finaly);
  sendToAllClient(data, MOVEMENT, UPDATEBULLET);
}

void	Game::moveBullet(GameParam&)
{
  Position p;
  PacketData	*data = new PacketData;
  std::list<Bullet>::iterator it = this->_bullets.begin();
  short		finalx;
  short		finaly;

  if (this->_bullets.size() > 0)
    {
      data->addShort(this->_bullets.size());
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
	  data->addShort(finalx);
	  data->addShort(finaly);
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
  std::map<int, AObject *>::iterator it2 = this->_monster.begin();

  while (it != this->_players.end())
    {
      if (it->first == name)
	return (it->second);
      ++it;
    }
/*  it2 = this->_monster.begin();
  while (it2 != this->_monster.end())
    {
      if (it2->first == 0)
	return (it2->second);
      ++it2;
    }*/
  std::cout << "no PLAYER FOUND" << std::endl;
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

int Game::nbBullet()
{
	ScopedLock sl(this->_mutex);

	return (this->_bullets.size());
}

int	Game::getNbMonster()
{
  ScopedLock sl(this->_mutex);

  return (this->_monster.size());
}
