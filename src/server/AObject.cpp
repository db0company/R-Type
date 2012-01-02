#include "AObject.hpp"


AObject::AObject()
{

}

AObject::AObject(const AObject& old)
{
  this->pos = old.pos;
  this->name = old.name;
  this->type = old.type;
}

AObject::~AObject()
{

}

const std::string &AObject::getName()const
{
  return (this->name);
}

void		AObject::setPos(const Position& newPos)
{
  pos = newPos;
}

const Position&	AObject::getPos()const
{
  return (this->pos);
}

AObject	&AObject::operator=(const AObject& old)
{
  this->pos = old.pos;
  this->name = old.name;
  this->type = old.type;
  return (*this);
}
