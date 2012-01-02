#include <map>
#include "Player.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Game.hpp"

Game::Game(const GameParameter& param)
{
  
  _param = param;
  // On va faire quelques tests.
  
  createNewPlayer(NULL, "Player1");
  createNewPlayer(NULL, "Player2");
  createNewMonster(NULL);
  createNewMonster(NULL);
  createWall();
}

Game::~Game()
{

}

Game::Game(const Game& old)
{
  this->_param = old._param;
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




Game&	Game::operator=(const Game& old)
{
  this->_param = old._param;
  return (*this);
}
