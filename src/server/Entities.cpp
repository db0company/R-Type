#include "Entities.hpp"

Entities::Entities()
  : AObject()
{
  this->life = 100;
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
