#include "Entities.hpp"

Entities::Entities()
  : AObject()
{
  this->life = 3;
  this->power = 1;
}

Entities::~Entities()
{

}

Entities::Entities(const Entities& old)
  : AObject()
{
  this->life = old.life;
  this->power = old.power;
}

Entities	&Entities::operator=(const Entities& old)
{
  this->life = old.life;
  this->power = old.power;
  return (*this);
}

void		Entities::changeLife(int ch)
{
  this->life -= ch;
}

eGroup		Entities::getGroup()const
{
  return (this->group);
}

void		Entities::die()
{
  this->life = 0;
}

bool		Entities::isDie()const
{
  if (this->life == 0)
    return (true);
  return (false);
}

int		Entities::getLife()const
{
  return (this->life);
}
