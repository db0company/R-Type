#include <map>
#include "Player.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Game.hpp"

Game::Game(const GameParameter& param)
{
  AObject	*truc;
  
  _param = param;

  // On va faire quelques tests.
  
  createNewPlayer(NULL, "Player1");
  createNewPlayer(NULL, "Player2");
  createNewMonster(NULL);
  createNewMonster(NULL);

   truc = new Tile;
  this->_map.insert(std::pair<std::string, AObject *>("tile1", truc));
  truc = new Tile;
  this->_map.insert(std::pair<std::string, AObject *>("tile2", truc));
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

const std::string Game::getPlayerByIp(const std::string& ip)
{
  std::map<std::string, AObject *>::iterator it = this->_players.begin();

  while (it != this->_players.end())
    {
      if (reinterpret_cast<Player *>(it->second)->getIp() == ip)
	return (it->first);
      ++it;
    }
  //error
  return ("");
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

Game&	Game::operator=(const Game& old)
{
  this->_param = old._param;
  return (*this);
}
