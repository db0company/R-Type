#include "Position.hpp"

Position::Position(float v1, float v2)
{
  x = v1;
  y = v2;
}

Position::Position()
{
  x = 0;
  y = 0;
}

Position::Position(const Position& old)
{
  this->x = old.x;
  this->y = old.y;
}

Position::~Position()
{

}

bool		Position::operator=(const Position& old)const
{
  if (this->x == old.x && this->y == old.y)
    return (true);
  return (false);
}

Position	&Position::operator=(const Position& old)
{
  this->x = old.x;
  this->y = old.y;
  return (*this);
}
