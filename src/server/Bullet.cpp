#include "Bullet.hpp"

Bullet::Bullet(Position p, eGroup g)
{
  this->pos = p;
  this->group = g;
}

Bullet::~Bullet()
{

}

const Position&	Bullet::getPos()const
{
  return (this->pos);
}

void	Bullet::setPos(const Position& p)
{
  this->pos = p;
}

eGroup	Bullet::getGroup()const
{
  return (this->group);
}
