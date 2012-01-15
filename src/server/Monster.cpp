#include <iostream>
#include "enum.h"
#include "Monster.hpp"

Monster::Monster()
{
  this->group = ENNEMY;
  this->MType = 0;
}

Monster::~Monster()
{

}

Monster::Monster(const Monster& old)
	: Entities(old)
{
	this->group = old.group;
	this->MType = old.MType;
}

Monster& Monster::operator=(const Monster& old)
{
	this->group = old.group;
	this->MType = old.MType;
	return (*this);
}

void		Monster::setMType(int type)
{
  this->MType = type;
}

int		Monster::getMType()const
{
  return (this->MType);
}

void		Monster::setMId(int id)
{
  this->MId = id;
}

int		Monster::getMId()const
{
  return (this->MId);
}
