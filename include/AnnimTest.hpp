#ifndef ANNIMTEST_H
# define ANNIMTEST_H

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "IAnnim.hpp"

namespace LibGraphic
{

  class AnnimTest : public IAnnim
  {

    AnnimTest();
  public:
    AnnimTest(sf::RenderWindow &, sf::Sprite &, unsigned int nbPlay = 0);
    ~AnnimTest();

  public:
    virtual void play();
    virtual void pause();
    virtual void stop();

  public:
    virtual Coord const & getCoord() const;
    virtual void setCoord(Coord const &);
    virtual void setCoord(unsigned int, unsigned int);
    virtual void setScale(float, float);

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
    unsigned int _nbPlay;
    unsigned int _currentSprite;

  };

}

#endif
