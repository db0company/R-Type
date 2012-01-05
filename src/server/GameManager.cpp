#include "GameManager.hpp"

GameManager::GameManager(GameManager const &other)
{
}

GameManager& GameManager::operator=(GameManager const &other)
{
  return (*this);
}

GameManager::GameManager(void)
{
}

GameManager::~GameManager(void)
{
}

bool GameManager::createGame(GameParameter const &param)
{
  Game *new_game = new Game(param);

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

// bool GameManager::delPlayerFromGame(User *user)
// {
// }

Game *GameManager::getGameFromId(unsigned int id)
{
  if (this->_gameMap.find(id) == this->_gameMap.end())
    {
      return (NULL);
    }
  return (this->_gameMap[id]);
}

