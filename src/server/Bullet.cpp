#include "Bullet.hpp"

Bullet::Bullet(Position p, eGroup g)
{
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
