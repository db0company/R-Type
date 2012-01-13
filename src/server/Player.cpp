#include "enum.h"
#include "Player.hpp"

Player::Player(User *u, const std::string& n)
 : Entities()
{
  this->group = FRIENDS;
  this->name = n;
  this->us = u;
  this->id = 0;
}

Player::~Player()
{

}

const std::string&	Player::getIp()const
{
  return (this->us->getIp());
}

User		*Player::getUser()
{
  return (this->us);
}

int		Player::getId()const
{
  return (this->id);
}

void		Player::setId(int i)
{
  this->id = i;
}
