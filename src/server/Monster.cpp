#include <iostream>
#include "enum.h"
#include "Monster.hpp"

Monster::Monster()
{
  this->group = ENNEMY;
}

Monster::~Monster()
{

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
