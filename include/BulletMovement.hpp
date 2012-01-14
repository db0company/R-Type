#ifndef BULLETMOVEMENT_H
# define BULLETMOVEMENT_H

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "SpriteInfo.hpp"

namespace LibGraphic
{

  class BulletMovement
  {

  public:
    BulletMovement(sf::RenderWindow &, sf::Sprite &, eBulletType e = NORMAL_BULLET);
    ~BulletMovement(){}

  public:
    void draw();

  public:
    Coord const & getCoord() const;
    void setCoord(Coord const & coord);
    int getX(void) const;
    int getY(void) const;

   private:
    sf::RenderWindow & _app;
    sf::Sprite & _sprite;
    Coord _coord;
    eBulletType _btype;
  };

}

#endif
