#include "GameManager.hpp"

GameManager::GameManager(GameManager const &other)
{
  this->_userMap = other._userMap;
  this->_roomMap = other._roomMap;
  this->_gameMap = other._gameMap;
}

GameManager& GameManager::operator=(GameManager const &other)
{
  this->_userMap = other._userMap;
  this->_roomMap = other._roomMap;
  this->_gameMap = other._gameMap;
  return (*this);
}

GameManager::GameManager(void)
{
}

GameManager::~GameManager(void)
{
}

bool GameManager::createRoom(GameParameter const &)
{
  //todo
  return (false);
}

bool GameManager::createGame(GameParameter const &)
{
  //todo
  return (false);
}
