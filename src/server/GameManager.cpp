#include "Server.hpp"
#include "PacketTask.hpp"
#include "GameManager.hpp"

GameManager::GameManager(GameManager const &other)
{
  this->_gameMap = other._gameMap;
}

GameManager& GameManager::operator=(GameManager const &other)
{
  this->_gameMap = other._gameMap;
  return (*this);
}

GameManager::GameManager(void)
{
}

GameManager::~GameManager(void)
{
}

bool	GameManager::addGame(Game *new_game)
{
  this->_gameMap[new_game->getId()] = new_game;
  return (true);
}


bool GameManager::addPlayerToGame(User *user, unsigned int game_id,
				  std::string const &log, bool root, bool observer)
{
  if (this->_gameMap.find(game_id) == this->_gameMap.end())
    {
      return (false);
    }
  return (this->_gameMap[game_id]->addUser(user, root, observer, log));
}

Game *GameManager::getGameFromId(unsigned int id)
{
  if (this->_gameMap.find(id) == this->_gameMap.end())
    {
      return (NULL);
    }
  return (this->_gameMap[id]);
}

Game *GameManager::getGameFromName(std::string const &name)
{
  std::map<int, Game *>::iterator it;
  Game *tmp;

  for (it = this->_gameMap.begin(); it != this->_gameMap.end(); ++it)
    {
      tmp = it->second;
      if (tmp->getName() == name)
	{
	  return (tmp);
	}
    }
  return (NULL);
}

std::map<int, Game *> &GameManager::getGames(void)
{
  return (this->_gameMap);
}

Game *GameManager::getGameFromUser(User *us)
{
  std::map<int, Game *>::iterator it;
  std::map<std::string, AObject *> list;
  std::map<std::string, AObject *>::iterator it2;
  Game *tmp;

  for (it = this->_gameMap.begin(); it != this->_gameMap.end(); ++it)
    {
      tmp = it->second;
      list = tmp->getPlayerList();
      it2 = list.begin();
      while (it2 != list.end())
	{
	  if (static_cast<Player *>(it2->second)->getUser() == us)
	    return (tmp);
	  ++it;
	}
    }
  return (NULL);
}

void		GameManager::updateAll(Server& serv)
{
  std::map<int, Game *>::iterator it = this->_gameMap.begin();
  PacketTask *pt;
  PacketData *d = new PacketData;

  // std::cout << "time to up all" << std::endl;
  while (it != this->_gameMap.end())
    {
      if (it->second->getNbMonster() > 0)
	{
	  pt = new PacketTask(&Game::moveMonster, d, it->second, NULL);
	  serv.getTaskQueue().push(pt);
	  serv.getCondVar()->signal();
	}
      ++it;	  
    }
  it = this->_gameMap.begin();
  while (it != this->_gameMap.end())
    {
      if (it->second->getStatus() == INGAME && it->second->nbBullet() > 0)
	{
	  pt = new PacketTask(&Game::moveBullet, d, it->second, NULL);
	  serv.getTaskQueue().push(pt);
	  serv.getCondVar()->signal();
	}
      ++it;
    }
  it = this->_gameMap.begin();
  while (it != this->_gameMap.end())
    {
      if (it->second->nbBullet() > 0)
	{
	  pt = new PacketTask(&Game::checkCollision, d, it->second, NULL);
	  serv.getTaskQueue().push(pt);
	  serv.getCondVar()->signal();
	}
      ++it;
    }
}
