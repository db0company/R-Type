#include "InfoGame.hpp"

InfoGame::InfoGame(void) : _id(0), _owner(""), _name(""), _map(""), _obs(false),
			   _players(1), _player_max(1)
{
}

InfoGame::~InfoGame(void)
{
}

InfoGame::InfoGame(const InfoGame&o)
{
  this->_id = o._id;
  this->_owner = o._owner;
  this->_name = o._name;
  this->_map = o._name;
  this->_obs = o._obs;
  this->_players = o._players;
  this->_player_max = o._player_max;
}

InfoGame&	InfoGame::operator=(const InfoGame&o)
{
  this->_id = o._id;
  this->_owner = o._owner;
  this->_name = o._name;
  this->_map = o._name;
  this->_obs = o._obs;
  this->_players = o._players;
  this->_player_max = o._player_max;
  return (*this);
}

unsigned int	InfoGame::getId(void) const
{
  return (this->_id);
}

std::string const & InfoGame::getOwner(void) const
{
  return (this->_owner);
}

std::string const & InfoGame::getName(void) const
{
  return (this->_name);
}

std::string const & InfoGame::getMap(void) const
{
  return (this->_map);
}

bool		InfoGame::getObs(void) const
{
  return (this->_obs);
}

unsigned int	InfoGame::getPlayers(void) const
{
  return (this->_players);
}

unsigned int	InfoGame::getPlayerMax(void) const
{
  return (this->_player_max);
}

void InfoGame::setId(unsigned int id)
{
  this->_id = id;
}

void InfoGame::setOwner(std::string const &owner)
{
  this->_owner = owner;
}

void InfoGame::setName(std::string const &name)
{
  this->_name = name;
}

void InfoGame::setMap(std::string const &map)
{
  this->_map = map;
}

void InfoGame::setObs(bool o)
{
  this->_obs = o;
}

void InfoGame::setPlayers(unsigned int p)
{
  this->_players = p;
}

void InfoGame::setPlayerMax(unsigned int p)
{
  this->_player_max = p;
}
