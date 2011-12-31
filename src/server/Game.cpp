#include <map>
#include "Player.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Game.hpp"

Game::Game(const GameParameter& param)
{
  AObject	*truc = new Player;
  
  _param = param;

  // On va faire quelques tests.
  this->_players.insert(std::pair<std::string, AObject *>("player1", truc));
  truc = new Player;
  this->_players.insert(std::pair<std::string, AObject *>("player2", truc));
  
  truc = new Monster;
  this->_monster.insert(std::pair<std::string, AObject *>("monster1", truc));
  truc = new Monster;
  this->_monster.insert(std::pair<std::string, AObject *>("monster2", truc));
  
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

void	Game::changePlayerPos()
{

}

Game&	Game::operator=(const Game& old)
{
  this->_param = old._param;
  return (*this);
}
