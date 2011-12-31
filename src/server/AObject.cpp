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

AObject	&AObject::operator=(const AObject& old)
{
  this->pos = old.pos;
  this->name = old.name;
  this->type = old.type;
  return (*this);
}
