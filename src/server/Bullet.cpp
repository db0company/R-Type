#include "Bullet.hpp"

Bullet::Bullet(Position p, eGroup g, const std::string& ow)
{
  this->owner = ow;
  this->pos = p;
  this->group = g;
  this->toDestroy = false;
}

Bullet::~Bullet()
{

}

eGroup	Bullet::getGroup()const
{
  return (this->group);
}

void	Bullet::setDestroy()
{
  this->toDestroy = true;
}

bool	Bullet::getDestroy()
{
  return (this->toDestroy);
}

void	Bullet::setOwner(const std::string& ow)
{
  this->owner = ow;
}

const std::string& Bullet::getOwner()const
{
  return (this->owner);
}
