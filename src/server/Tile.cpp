#include "Tile.hpp"

Tile::Tile()
{

}

Tile::~Tile()
{

}

eTileName	Tile::getTileType()const
{
  return (this->tileType);
}

void		Tile::setTileType(eTileName t)
{

  this->tileType = t;
}

Tile::Tile(eTileName t)
{
 this->tileType = t;
}

Tile&	Tile::operator=(const Tile& old)
{
  this->tileType = old.tileType;
  return (*this);
}
