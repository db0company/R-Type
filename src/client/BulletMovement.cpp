#include <iostream>
#include "SpriteInfo.hpp"
#include "BulletMovement.hpp"

LibGraphic::BulletMovement::BulletMovement(sf::RenderWindow & app,
					   sf::Sprite & sprite, eBulletType e):
  _app(app), _sprite(sprite)
{
  this->_coord.x = 0;
  this->_coord.y = 0;
  this->_btype = e;
}

void LibGraphic::BulletMovement::draw()
{
  // subrect ?
  std::list<Coord *>::iterator it;
  for (it = this->_coordList.begin(); it != this->_coordList.end(); ++it)
    {
      this->_sprite.SetPosition((*it)->x, (*it)->y);
      this->_sprite.SetSubRect(sf::IntRect(0,0,50,50));
      this->_app.Draw(this->_sprite);
    }
}

LibGraphic::Coord const & LibGraphic::BulletMovement::getCoord() const
{
  return this->_coord;
}

void LibGraphic::BulletMovement::setCoord(LibGraphic::Coord const & coord)
{
  this->_coord.x = coord.x;
  this->_coord.y = coord.y;
}

int LibGraphic::BulletMovement::getX(void) const
{
  return (this->_coord.x);
}

int LibGraphic::BulletMovement::getY(void) const
{
  return (this->_coord.y);
}

std::list<LibGraphic::Coord *> & LibGraphic::BulletMovement::getCoordList()
{
  return this->_coordList;
}
