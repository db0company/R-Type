#include "Position.hpp"

Position::Position(int v1, int v2)
{
  x = v1;
  y = v2;
  this->tilex = 0;
  this->tiley = 0;
}

Position::Position()
{
  x = 0;
  y = 0;
  this->tilex = 0;
  this->tiley = 0;
}

Position::Position(const Position& old)
{
  this->x = old.x;
  this->y = old.y;
}

Position::~Position()
{

}

int		Position::getX()const
{
  return (this->x);
}

int		Position::getY()const
{
  return (this->y);
}

bool		Position::operator==(const Position& old)const
{
  if (this->x == old.getX() && this->y == old.getY())
    return (true);
  return (false);
}

Position	&Position::operator=(const Position& old)
{
  this->x = old.x;
  this->y = old.y;
  this->tilex = old.tilex;
  this->tiley = old.tiley;
  return (*this);
}
