#include <iostream>
#include <map>
#include <string>
// #include <pair>
#include "Player.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Game.hpp"
#include "User.hpp"

unsigned int Game::_sid = 0;

Game::Game() : _owner_login(""), _name(""), _lvlname(""), player_max(4),
	       _observer(true), _status(LOBBYROOM)
{
  // On va faire quelques tests.

  createNewPlayer(NULL, "Player1");
  createNewPlayer(NULL, "Player2");
  createNewMonster(NULL);
  createNewMonster(NULL);
  createWall();

  this->_id = this->_sid;
  ++(this->_sid);
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
  this->_userObsMap = old._userObsMap;
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
  this->_userObsMap = old._userObsMap;
  this->_owner_login = old._owner_login;
  this->_name = old._name;
  this->_lvlname = old._lvlname;
  this->player_max = old.player_max;
  this->_observer = old._observer;
  this->_status = old._status;
  return (*this);
}

void	Game::changePlayerPos(void *)
{
  std::string ip; // a extraire du packet
  std::string ret;
  std::map<std::string, AObject *>::iterator it;
  Position newPos;

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
  it->second->setPos(newPos);
}

void	Game::moveMonster(void *)
{
  std::map<std::string, AObject *>::iterator it = this->_monster.begin();

  while (it != this->_monster.end())
    {
      reinterpret_cast<Monster *>(it->second)->moveNextPos();
      ++it;
    }
  // create packet move monster dans 1 s
}

void	Game::createNewPlayer(User *us, const std::string& name)
{
  Player	*newPlayer = new Player(us, name);

  this->_players.insert(std::pair<std::string, AObject *>(name, newPlayer));
}

void	Game::createNewMonster(void *)
{
  AObject *truc;
  int	i = 0;

  while (i != 3)
    {
      truc = new Monster;
      // initialisation du monstre
      this->_monster.insert(std::pair<std::string, AObject *>("monster", truc));
      ++i;
    }
  // creer un nouveau paquet create new monster
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

void	Game::checkCollision(void *)
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
	      // kill player; NE PAS DETRUIRE LE MAILLON ICI
	      // destroy la bullet MAIS PAS ICI
	    }
	  ++itM;
	}
      while (itM != this->_monster.end())
	{
	  if (itP->second->getPos() == itM->second->getPos())
	    {
	      // kill player; NE PAS DETRUIRE LE MAILLON ICI
	    }
	  ++itM;
	}
      ++itP;
    }
}

void	Game::moveBullet(void *)
{
  Position p;
  std::list<Bullet>::iterator it = this->_bullets.begin();

  while (it != this->_bullets.end())
    {
      p = (*it).getPos();
      p.x--;
      (*it).setPos(p);
      ++it;
    }
}

void	Game::moveWall(void *)
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

  while (i != this->_param.sizeCol)
    {
      j = 0;
      while (j != this->_param.sizeLine)
	{
	  newLine.push_front(new Tile);
	  ++j;
	}
      ++i;
      this->_map.push_back(newLine);
    }
}

void	Game::fireBullet(void *)
{
  AObject *ent = NULL;
  eGroup	g;

  g = reinterpret_cast<Entities *>(ent)->getGroup();
  this->_bullets.push_front(Bullet(ent->getPos(), g));
}

bool Game::addUser(User *user, bool root, bool observer, std::string const &login)
{
  if (this->_userMap.size() > this->player_max)
    return (false);
  if (root)
    this->_owner_login = login;
  if (observer)
    this->_userMap.insert(std::pair<std::string, User *>(user->getIp(), user));
  else
    this->_userObsMap.insert(std::pair<std::string, User *>(user->getIp(), user));
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
