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
