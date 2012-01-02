#include "Player.hpp"

Player::Player(User *u, const std::string& n)
 : Entities()
{
  this->name = n;
  this->us = u;
}

Player::~Player()
{

}

const std::string&	Player::getIp()const
{
  return (this->us->getIp());
}
