#ifndef ANNIMBIGEXPLOSION_H
# define ANNIMBIGEXPLOSION_H

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "IAnnim.hpp"

namespace LibGraphic
{

  class AnnimBigExplosion : public IAnnim
  {

    AnnimBigExplosion();
  public:
    AnnimBigExplosion(sf::RenderWindow &, sf::Sprite &, int nbPlay = 1);
    ~AnnimBigExplosion();

  public:
    virtual void play();
    virtual void pause();
    virtual void stop();

  public:
    virtual Coord const & getCoord() const;
    virtual void setCoord(Coord const &);
    virtual void setCoord(int, int);
    virtual void setScale(float x, float y);
    virtual float getTimer() const;
    virtual void setTimer(float);

  private:
    sf::RenderWindow & _app;
    Coord _coord;
    sf::Clock _clock;
    float _clockVal;
    sf::Sprite & _sprite;
    unsigned int _width;
    unsigned int _height;
    unsigned int _nbSprite;
    int _nbPlay;
    unsigned int _currentSprite;

  };

}

#endif
