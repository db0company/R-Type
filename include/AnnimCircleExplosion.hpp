#ifndef ANNIMCIRCLEEXPLOSION_H
# define ANNIMCIRCLEEXPLOSION_H

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "IAnnim.hpp"

namespace LibGraphic
{

  class AnnimCircleExplosion : public IAnnim
  {

    AnnimCircleExplosion();
  public:
    AnnimCircleExplosion(sf::RenderWindow &, sf::Sprite &, int nbPlay = 1);
    ~AnnimCircleExplosion();

  public:
    virtual void play();
    virtual void pause();
    virtual void stop();

  public:
    virtual Coord const & getCoord() const;
    virtual void setCoord(Coord const &);
    virtual void setCoord(int ,int);
    virtual float getTimer() const;
    virtual void setTimer(float);
    virtual void setScale(float x, float y);
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
