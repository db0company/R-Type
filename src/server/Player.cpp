#include "enum.h"
#include "Player.hpp"

Player::Player(User *u, const std::string& n)
 : Entities()
{
  this->group = FRIENDS;
  this->name = n;
  this->us = u;
  this->id = 0;
  this->score = 0;
}

Player &Player::operator=(Player const &p)
{
  this->group = p.group;
  this->name = p.name;
  this->us = p.us;
  this->id = p.id;
  this->score = p.score;
  return *this;
}

Player::Player(Player const &p) : Entities(p)
{
  this->group = p.group;
  this->name = p.name;
  this->us = p.us;
  this->id = p.id;
  this->score = p.score;
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

void		Player::AddToScore(int i)
{
  this->score += i;
}

int		Player::getScore()const
{
  return (this->score);
}
