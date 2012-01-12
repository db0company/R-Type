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
    Coord const & getCoord() const;
    void setCoord(Coord const &);

    float getTimer() const;
    void setTimer(float);
  private:
    int MapX(int x);
    int MapY(int y);

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
